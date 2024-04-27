// Copyright (c) 2024, PortalPlayer <email@portalplayer.xyz>
// Licensed under MIT <https://opensource.org/licenses/MIT>

#include <BaconAPI/ArgumentHandler.h>
#include <cURL.h>
#include <Settings.h>
#include <string.h>
#include <BaconAPI/String.h>

int main(int argc, char** argv) {
    BA_ArgumentHandler_Initialize(argc, argv);
    SBR_Settings_Load();
    BA_LOGGER_INFO("Initializing curl\n");
    SBR_cURL_Initialize(NULL);

    char* test = BA_String_CreateEmpty();
    
    SBR_cURL_HTTPSend("http://example.com", "{}", BA_BOOLEAN_FALSE, &test);
    BA_LOGGER_INFO("%s\n", test);
    BA_LOGGER_INFO("Closing cURL\n");
    SBR_cURL_Close(BA_BOOLEAN_TRUE);
    free(test);
}
