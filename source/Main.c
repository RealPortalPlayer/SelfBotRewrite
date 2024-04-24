// Copyright (c) 2024, PortalPlayer <email@portalplayer.xyz>
// Licensed under MIT <https://opensource.org/licenses/MIT>

#include <stdio.h>
#include <BaconAPI/ArgumentHandler.h>
#include <BaconAPI/Logger.h>

#include "Settings.h"
#include "WebSocket/cURL.h"

int main(int argc, char** argv) {
    BA_ArgumentHandler_Initialize(argc, argv);
    SBR_Settings_Load();
    BA_LOGGER_INFO("Starting curl\n");
    BA_LOGGER_DEBUG("Discord:\n"
                    "API version: %i\n"
                    "API URL: %s\n"
                    "WebSocket URL: %s\n"
                    "libcurl: %s\n", DISCORD_API_VERSION, DISCORD_API_URL, DISCORD_WEBSOCKET_URL, curl_version());
    SBR_cURL_Initialize();
    return 0;
}
