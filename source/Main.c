// Copyright (c) 2024, PortalPlayer <email@portalplayer.xyz>
// Licensed under MIT <https://opensource.org/licenses/MIT>

#include <stdio.h>
#include <Token.h>
#include <BaconAPI/ArgumentHandler.h>
#include <BaconAPI/Logger.h>

#include "Settings.h"

int main(int argc, char** argv) {
    BA_ArgumentHandler_Initialize(argc, argv);
    SBR_Settings_Load();
    BA_LOGGER_INFO("%s\n", SBR_Token_Get());
    return 0;
}
