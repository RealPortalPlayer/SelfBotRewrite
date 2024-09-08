// Copyright (c) 2024, PortalPlayer <email@portalplayer.xyz>
// Licensed under MIT <https://opensource.org/licenses/MIT>

#include <BaconAPI/ArgumentHandler.h>
#include <BaconAPI/Logger.h>
#include <cURL.h>
#include <Settings.h>
#include <Discord/API/Events.h>

int main(int argc, char** argv) {
    BA_ArgumentHandler_Initialize(argc, argv);
    SBR_Settings_Load();
    SBR_cURL_LoopInitialize(NULL);

    SBR_Snowflake* snowflake = SBR_Snowflake_ConvertFromNumber(570600829330128906);
    
    SBR_DiscordAPIEvents_SendMessage(snowflake, "Hello, from APITest", NULL);
    SBR_cURL_Close(BA_BOOLEAN_TRUE);
}
