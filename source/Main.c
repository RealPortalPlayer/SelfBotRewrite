// Copyright (c) 2024, PortalPlayer <email@portalplayer.xyz>
// Licensed under MIT <https://opensource.org/licenses/MIT>

#include <BaconAPI/ArgumentHandler.h>
#include <BaconAPI/Logger.h>
#include <signal.h>

#include "Settings.h"
#include "cURL.h"
#include "BuiltInArguments.h"
#include "Discord/Configuration.h"
#include "Discord/Gateway/Event.h"
#include "MainLoop.h"
#include "Threads/Heartbeat.h"
#include "Threads/RateLimit.h"
#include "BotSetup.h"
#include "Commands/Command.h"
#include "Commands/Category.h"

void SignalHandler(int signal) {
    if (signal != SIGINT)
        return;
    
    SBR_MainLoop_Shutdown();
}

int main(int argc, char** argv) {
    BA_ArgumentHandler_Initialize(argc, argv);
    BA_LOGGER_DEBUG("Registering signals\n");
    signal(SIGINT, &SignalHandler);

    if (BA_ArgumentHandler_ContainsArgumentOrShort(SBR_BUILTINARGUMENTS_HELP, SBR_BUILTINARGUMENTS_HELP_SHORT, BA_BOOLEAN_FALSE)) {
        BA_LOGGER_INFO("Arguments:\n%s\n"
                       BA_ARGUMENTHANDLER_HELP_MESSAGE(SBR_BUILTINARGUMENTS_CURL_VERBOSE, SBR_BUILTINARGUMENTS_CURL_VERBOSE_SHORT, "cURL verbose messages\n")
                       BA_ARGUMENTHANDLER_HELP_MESSAGE(SBR_BUILTINARGUMENTS_HELP, SBR_BUILTINARGUMENTS_HELP_SHORT, "Shows information about each argument\n")
                       BA_ARGUMENTHANDLER_HELP_MESSAGE_ARGUMENTS(SBR_BUILTINARGUMENTS_DISCORD_API, "<version>", SBR_BUILTINARGUMENTS_DISCORD_API_SHORT, "Use custom Discord API version\n")
                       BA_ARGUMENTHANDLER_HELP_MESSAGE_ARGUMENTS(SBR_BUILTINARGUMENTS_DISCORD_API_ROOT, "<url>", SBR_BUILTINARGUMENTS_DISCORD_API_ROOT_SHORT, "Use custom Discord API root\n")
                       BA_ARGUMENTHANDLER_HELP_MESSAGE_ARGUMENTS(SBR_BUILTINARGUMENTS_DISCORD_WEBSOCKET, "<url>", SBR_BUILTINARGUMENTS_DISCORD_WEBSOCKET_SHORT, "Use custom Discord WebSocket\n"
                       BA_ARGUMENTHANDLER_HELP_MESSAGE_ARGUMENTS(SBR_BUILTINARGUMENTS_DISCORD_CDN, "<url>", SBR_BUILTINARGUMENTS_DISCORD_CDN_SHORT, "Use custom Discord CDN\n")
                       BA_ARGUMENTHANDLER_HELP_MESSAGE_ARGUMENTS(SBR_BUILTINARGUMENTS_EVENT_BUFFER, "<size>", SBR_BUILTINARGUMENTS_EVENT_BUFFER_SHORT, "Size in characters for the event buffer\n")), BA_ArgumentHandler_GetHelpMessage());
        return BA_BOOLEAN_TRUE;
    }
    
    BA_LOGGER_INFO("Starting bot (internal version: " SBR_VERSION ")\n");
    SBR_Settings_Load();
    BA_LOGGER_DEBUG("Discord:\n"
                    "API version: %i\n"
                    "API URL: %s\n"
                    "CDN URL: %s\n"
                    "libcurl: %s\n", SBR_DiscordConfiguration_GetAPIVersion(), SBR_DiscordConfiguration_GetAPIURL(NULL), SBR_DiscordConfiguration_GetCDNURL(NULL), curl_version());

    if (SBR_DiscordConfiguration_GetAPIVersion() <= SBR_DISCORD_DEPRECATED_API_VERSION)
        BA_LOGGER_WARN("Discord API version %i and below are deprecated. Expect problems\n", SBR_DISCORD_DEPRECATED_API_VERSION);

    BA_LOGGER_INFO("Creating threads\n");
    SBR_HeartbeatThread_Create();
    SBR_RateLimitClearerThread_Create();
    SBR_RateLimitDetecterThread_Create();
    SBR_Command_Initialize();
    SBR_Category_Initialize();
    // TODO: Console command thread
    SBR_BotSetup_Main();

    while (BA_BOOLEAN_TRUE) {
        if (!SBR_MainLoop_Start()) {
            SBR_HeartbeatThread_Pause(BA_BOOLEAN_TRUE);
            continue;
        }

        break;
    }

    SBR_Category_Destroy();
    SBR_Command_Destroy();
    BA_LOGGER_INFO("Closing threads (press CTRL+C if frozen)\n");
    SBR_RateLimitDetecterThread_Destroy();
    SBR_RateLimitClearerThread_Destroy();
    SBR_HeartbeatThread_Pause(BA_BOOLEAN_TRUE);
    SBR_HeartbeatThread_Destroy();
    return 0;
}

