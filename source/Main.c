// Copyright (c) 2024, PortalPlayer <email@portalplayer.xyz>
// Licensed under MIT <https://opensource.org/licenses/MIT>

#include <BaconAPI/ArgumentHandler.h>
#include <BaconAPI/Logger.h>
#include <Threads/Heartbeat.h>
#include <BaconAPI/Internal/OperatingSystem.h>

#if BA_OPERATINGSYSTEM_POSIX_COMPLIANT
#   include <unistd.h>
#elif BA_OPERATINGSYSTEM_WINDOWS
#   include <Windows.h>
#endif

#include "Settings.h"
#include "WebSocket/cURL.h"
#include "BuiltInArguments.h"
#include "Discord/Configuration.h"
#include "Discord/Gateway/Event.h"
#include "Main.h"

#define SBR_MAIN_PACKET_BUFFER_SIZE 9000 // TODO: Get a more concrete number

static volatile BA_Boolean sbrMainDisconnected = BA_BOOLEAN_FALSE;

#ifndef SBR_STATIC
BA_Boolean SBR_Main_EntryPoint(void) {
    BA_LOGGER_INFO("Starting cURL\n");

    {
        BA_Boolean errored = BA_BOOLEAN_FALSE;

        while (BA_BOOLEAN_TRUE) {
            if (!SBR_cURL_Initialize(NULL)) {
                errored = BA_BOOLEAN_TRUE;
                
                BA_LOGGER_WARN("Retrying in 5 seconds...\n");
                sleep(5);
                continue;
            }

            break;
        }

        if (errored)
            BA_LOGGER_INFO("Finally connected\n");
    }
    
    while (BA_BOOLEAN_TRUE) {
        char buffer[SBR_MAIN_PACKET_BUFFER_SIZE];
        size_t receivedBytes;
        const struct curl_ws_frame* metadata;

        if (!SBR_cURL_Receive(buffer, SBR_MAIN_PACKET_BUFFER_SIZE, &receivedBytes, &metadata)) {
            if (sbrMainDisconnected)
                break;

            continue;
        }

        buffer[receivedBytes] = '\0';
        SBR_GatewayEvent_Parse(buffer);
    }

    BA_LOGGER_INFO("Closing cURL\n");
    SBR_cURL_Close();
    return !sbrMainDisconnected;
}

int main(int argc, char** argv) {
    BA_ArgumentHandler_Initialize(argc, argv);

    if (BA_ArgumentHandler_ContainsArgumentOrShort(SBR_BUILTINARGUMENTS_HELP, SBR_BUILTINARGUMENTS_HELP_SHORT, BA_BOOLEAN_FALSE)) {
        BA_LOGGER_INFO("Arguments:\n%s\n"
                       BA_ARGUMENTHANDLER_HELP_MESSAGE(SBR_BUILTINARGUMENTS_CURL_VERBOSE, SBR_BUILTINARGUMENTS_CURL_VERBOSE_SHORT, "cURL verbose messages\n")
                       BA_ARGUMENTHANDLER_HELP_MESSAGE(SBR_BUILTINARGUMENTS_HELP, SBR_BUILTINARGUMENTS_HELP_SHORT, "Shows information about each argument\n")
                       BA_ARGUMENTHANDLER_HELP_MESSAGE_ARGUMENTS(SBR_BUILTINARGUMENTS_DISCORD_API, SBR_BUILTINARGUMENTS_DISCORD_API_SHORT, "<version>", "Use custom Discord API version\n")
                       BA_ARGUMENTHANDLER_HELP_MESSAGE_ARGUMENTS(SBR_BUILTINARGUMENTS_DISCORD_API_ROOT, SBR_BUILTINARGUMENTS_DISCORD_API_ROOT_SHORT, "<url>", "Use custom Discord API root\n")
                       BA_ARGUMENTHANDLER_HELP_MESSAGE_ARGUMENTS(SBR_BUILTINARGUMENTS_DISCORD_WEBSOCKET, SBR_BUILTINARGUMENTS_DISCORD_WEBSOCKET_SHORT, "<url>", "Use custom Discord WebSocket\n"
                       BA_ARGUMENTHANDLER_HELP_MESSAGE_ARGUMENTS(SBR_BUILTINARGUMENTS_DISCORD_CDN, SBR_BUILTINARGUMENTS_DISCORD_CDN_SHORT, "<url>", "Use custom Discord CDN\n")), BA_ArgumentHandler_GetHelpMessage());
        return BA_BOOLEAN_TRUE;
    }
    
    SBR_Settings_Load();
    BA_LOGGER_DEBUG("Discord:\n"
                    "API version: %i\n"
                    "API URL: %s\n"
                    "WebSocket URL: %s\n"
                    "CDN URL: %s\n"
                    "libcurl: %s\n", SBR_DiscordConfiguration_GetAPIVersion(), SBR_DiscordConfiguration_GetAPIURL(NULL), SBR_DiscordConfiguration_GetWebSocketURL(), SBR_DiscordConfiguration_GetCDNURL(NULL), curl_version());

    if (SBR_DiscordConfiguration_GetAPIVersion() <= SBR_DISCORD_DEPRECATED_API_VERSION)
        BA_LOGGER_WARN("Discord API version %i and below are deprecated. Expect problems\n", SBR_DISCORD_DEPRECATED_API_VERSION);

    BA_LOGGER_INFO("Creating threads\n");
    SBR_HeartbeatThread_Create();
    // TODO: Console command thread
    // TODO: Heartbeat thread

    while (BA_BOOLEAN_TRUE) {
        if (!SBR_Main_EntryPoint()) {
            SBR_HeartbeatThread_Pause(BA_BOOLEAN_TRUE);
            
            sbrMainDisconnected = BA_BOOLEAN_FALSE;
            continue;
        }

        break;
    }

    BA_LOGGER_INFO("Closing threads (press CTRL+C if frozen)\n");
    SBR_HeartbeatThread_Destroy();
    return 0;
}
#endif

void SBR_Main_SignalDisconnected(void) {
    sbrMainDisconnected = BA_BOOLEAN_TRUE;
}
