// Copyright (c) 2024, PortalPlayer <email@portalplayer.xyz>
// Licensed under MIT <https://opensource.org/licenses/MIT>

#include <BaconAPI/Configuration.h>
#include <errno.h>
#include <string.h>
#include <BaconAPI/String.h>

#include "Settings.h"
#include "Debugging/Assert.h"

static BA_DynamicDictionary* sbrSensitiveSettingsParsed;
static BA_DynamicDictionary* sbrBotSettingsParsed;

BA_Boolean SBR_Settings_Get(const char* key, char** output, BA_Boolean sensitive) {
    *output = BA_DYNAMICDICTIONARY_GET_VALUE(char, sensitive ? sbrSensitiveSettingsParsed : sbrBotSettingsParsed, key, sizeof(char) * (strlen(key) + 1));

    BA_LOGGER_TRACE("%s Settings: %s=%s\n", sensitive ? "Sensitive" : "Bot", key, *output != NULL ? *output : "NULL");
    return *output != NULL;
}

void SBR_Settings_Load(void) {
    static BA_Boolean initialized = BA_BOOLEAN_FALSE;

    SBR_ASSERT(!initialized, "Settings are already initialized\n");
    BA_LOGGER_INFO("Loading sensitive settings\n");

    initialized = BA_BOOLEAN_TRUE;
    
    FILE* sensitive = fopen("sensitive.settings", "r");

    SBR_ASSERT(sensitive != NULL, "Failed to open sensitive settings file: %s\n", strerror(errno));

    sbrSensitiveSettingsParsed = BA_Configuration_ParseFromFile(sensitive);

    SBR_ASSERT(sbrSensitiveSettingsParsed != NULL, "Failed to parse sensitive settings file\n");
    fclose(sensitive);
    BA_LOGGER_INFO("Loading bot settings\n");

    FILE* bot = fopen("bot.settings", "r");

    SBR_ASSERT(bot != NULL, "Failed to open bot settings file: %s\n", strerror(errno));

    sbrBotSettingsParsed = BA_Configuration_ParseFromFile(bot);
    
    SBR_ASSERT(sbrBotSettingsParsed != NULL, "Failed to parse bot settings file\n");
}

BA_Boolean SBR_Settings_IsDevelopmentMode(void) {
    static BA_Boolean developmentMode = -1;

    if (developmentMode == -1) {
        char* type;

        developmentMode = SBR_Settings_Get("TYPE", &type, BA_BOOLEAN_TRUE) && BA_String_Equals(type, "development", BA_BOOLEAN_FALSE);
    }

    return developmentMode;
}
