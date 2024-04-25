// Copyright (c) 2024, PortalPlayer <email@portalplayer.xyz>
// Licensed under MIT <https://opensource.org/licenses/MIT>

#include <BaconAPI/ArgumentHandler.h>
#include <BaconAPI/Logger.h>

#include "Settings.h"
#include "WebSocket/cURL.h"
#include "BuiltInArguments.h"

int main(int argc, char** argv) {
    BA_ArgumentHandler_Initialize(argc, argv);
    
    if (BA_ArgumentHandler_ContainsArgumentOrShort(SBR_BUILTINARGUMENTS_HELP, SBR_BUILTINARGUMENTS_HELP_SHORT, BA_BOOLEAN_FALSE)) {
        BA_LOGGER_INFO("Arguments:\n%s\n"
                       BA_ARGUMENTHANDLER_HELP_MESSAGE(SBR_BUILTINARGUMENTS_CURL_VERBOSE, SBR_BUILTINARGUMENTS_CURL_VERBOSE_SHORT, "cURL verbose messages\n")
                       BA_ARGUMENTHANDLER_HELP_MESSAGE(SBR_BUILTINARGUMENTS_HELP, SBR_BUILTINARGUMENTS_HELP_SHORT, "Shows information about each argument\n"), BA_ArgumentHandler_GetHelpMessage());
        return 0;
    } 
    
    SBR_Settings_Load();
    BA_LOGGER_DEBUG("Discord:\n"
                    "API version: %i\n"
                    "API URL: %s\n"
                    "WebSocket URL: %s\n"
                    "libcurl: %s\n", DISCORD_API_VERSION, DISCORD_API_URL, DISCORD_WEBSOCKET_URL, curl_version());
    BA_LOGGER_INFO("Starting curl\n");
    SBR_cURL_Initialize(NULL);
    return 0;
}
