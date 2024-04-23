// Copyright (c) 2024, PortalPlayer <email@portalplayer.xyz>
// Licensed under MIT <https://opensource.org/licenses/MIT>

#include <BaconAPI/Configuration.h>
#include <BaconAPI/Debugging/Assert.h>

#include "Settings.h"

#include <errno.h>
#include <string.h>

static BA_DynamicDictionary* sbrSettingsParsed;

BA_Boolean SBR_Settings_Get(const char* key, char** output) {
    *output = BA_DYNAMICDICTIONARY_GET_VALUE(char, sbrSettingsParsed, key, sizeof(char) * (strlen(key) + 1));
    return *output != NULL;
}

void SBR_Settings_Load(void) {
    static BA_Boolean initialized = BA_BOOLEAN_FALSE;

    BA_ASSERT(!initialized, "Settings are already initialized\n");

    initialized = BA_BOOLEAN_TRUE;
    
    FILE* settings = fopen("bot.settings", "r");

    BA_ASSERT(settings != NULL, "Failed to open settings file: %s\n", strerror(errno));

    sbrSettingsParsed = BA_Configuration_ParseFromFile(settings);

    BA_ASSERT(sbrSettingsParsed != NULL, "Failed to parse settings file\n");
    fclose(settings);
}
