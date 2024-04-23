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
    SBR_cURL_Initialize();
    return 0;
}
