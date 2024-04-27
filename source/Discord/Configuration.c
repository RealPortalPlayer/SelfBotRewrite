// Copyright (c) 2024, PortalPlayer <email@portalplayer.xyz>
// Licensed under MIT <https://opensource.org/licenses/MIT>

#include <BaconAPI/Internal/Boolean.h>
#include <BaconAPI/Number.h>
#include <BaconAPI/ArgumentHandler.h>
#include <BaconAPI/String.h>
#include <json_object.h>
#include <json_tokener.h>

#include "Discord/Configuration.h"
#include "BuiltInArguments.h"
#include "cURL.h"

#define SBR_DISCORDCONFIGURATION_HACK_STRING2(string) #string
#define SBR_DISCORDCONFIGURATION_HACK_STRING1(string) SBR_DISCORDCONFIGURATION_HACK_STRING2(string)

#define SBR_DISCORDCONFIGURATION_ADD_PATH() \
if (path != NULL) {                         \
    char* cloned = BA_String_Copy(cached);  \
    if (!BA_String_EndsWith(&cloned, "/", BA_BOOLEAN_FALSE)) \
        BA_String_Append(&cloned, "/"); \
    return BA_String_Append(&cloned, path); \
} (void) NULL

#define SBR_DISCORDCONFIGURATION_ADD_NO_PATH()

#define SBR_DISCORDCONFIGURATION_SETUP_STRING(argument, short, default, path) \
initialized = BA_BOOLEAN_TRUE;                                          \
BA_ArgumentHandler_ShortResults results;                                \
if (BA_ArgumentHandler_GetInformationWithShort(argument, short, BA_BOOLEAN_FALSE, &results) == 0) { \
    cached = default;                                                   \
    SBR_DISCORDCONFIGURATION_ADD_ ## path();                                \
    return cached;                                                      \
} (void) NULL

#define SBR_DISCORDCONFIGURATION_SETUP_URL(prefix) \
if (!BA_String_StartsWith(cached, prefix "s://", BA_BOOLEAN_TRUE) && !BA_String_StartsWith(cached, prefix "://", BA_BOOLEAN_TRUE)) \
    BA_String_Prepend(&cached, prefix "s://");     \
if (!BA_String_EndsWith(cached, "/", BA_BOOLEAN_FALSE)) \
    BA_String_Append(&cached, "/")

int SBR_DiscordConfiguration_GetAPIVersion(void) {
    static int cached = SBR_DISCORD_API_VERSION;
    static BA_Boolean initialized = BA_BOOLEAN_FALSE;

    if (!initialized) {
        initialized = BA_BOOLEAN_TRUE;

        BA_ArgumentHandler_ShortResults results;

        if (BA_ArgumentHandler_GetInformationWithShort(SBR_BUILTINARGUMENTS_DISCORD_API, SBR_BUILTINARGUMENTS_DISCORD_API_SHORT, BA_BOOLEAN_FALSE, &results) != 0)
            cached = BA_Number_StringToInteger(*results.value, NULL, NULL, "Invalid Discord API version\n", SBR_DISCORD_API_VERSION);
    }

    return cached;
}

const char* SBR_DiscordConfiguration_GetAPIRootURL(void) {
    static char* cached = SBR_DISCORD_ROOT_URL;
    static BA_Boolean initialized = BA_BOOLEAN_FALSE;

    if (!initialized) {
        SBR_DISCORDCONFIGURATION_SETUP_STRING(SBR_BUILTINARGUMENTS_DISCORD_API_ROOT, SBR_BUILTINARGUMENTS_DISCORD_API_ROOT_SHORT, SBR_DISCORD_ROOT_URL, NO_PATH);
        
        cached = BA_String_Copy(*results.value);
    }

    return cached;
}

const char* SBR_DiscordConfiguration_GetAPIURL(const char* path) {
    static char* cached = NULL;

    if (cached == NULL) {
        if (!BA_ArgumentHandler_ContainsArgumentOrShort(SBR_BUILTINARGUMENTS_DISCORD_API, SBR_BUILTINARGUMENTS_DISCORD_API_SHORT, BA_BOOLEAN_FALSE) && !BA_ArgumentHandler_ContainsArgumentOrShort(SBR_BUILTINARGUMENTS_DISCORD_API_ROOT, SBR_BUILTINARGUMENTS_DISCORD_API_ROOT_SHORT, BA_BOOLEAN_FALSE)) {
            cached = SBR_DISCORD_API_URL;
            SBR_DISCORDCONFIGURATION_ADD_PATH();
            return cached;
        }
        
        cached = BA_String_Copy(SBR_DiscordConfiguration_GetAPIRootURL());
        
        SBR_DISCORDCONFIGURATION_SETUP_URL("http");
        BA_String_Append(&cached, "api/v%i");
        BA_String_Format(&cached, SBR_DiscordConfiguration_GetAPIVersion());
    }

    SBR_DISCORDCONFIGURATION_ADD_PATH();
    return cached;
}

const char* SBR_DiscordConfiguration_GetWebSocketURL(void) {
    static char* cached = NULL;
    static BA_Boolean initialized = BA_BOOLEAN_FALSE;

    if (!initialized) {
        char* buffer = BA_String_CreateEmpty();

        SBR_cURL_HTTPSend(SBR_DiscordConfiguration_GetAPIURL("gateway"), "{}", BA_BOOLEAN_FALSE, &buffer);

        json_object* object = json_tokener_parse(buffer);

        BA_ASSERT(object != NULL, "Failed to parse Gateway URL\n");
        
        json_object* url = json_object_object_get(object, "url");

        BA_ASSERT(url != NULL, "Failed to get Gateway URL\n");

        cached = BA_String_Copy(json_object_get_string(url));

        json_object_put(object);
        BA_String_Append(&cached, "?v=%i&encoding=json");
        BA_String_Format(&cached, SBR_DiscordConfiguration_GetAPIVersion());
    }

    return cached;
}

const char* SBR_DiscordConfiguration_GetCDNURL(const char* path) {
    static char* cached = SBR_DISCORD_ROOT_URL;
    static BA_Boolean initialized = BA_BOOLEAN_FALSE;

    if (!initialized) {
        SBR_DISCORDCONFIGURATION_SETUP_STRING(SBR_BUILTINARGUMENTS_DISCORD_CDN, SBR_BUILTINARGUMENTS_DISCORD_CDN_SHORT, SBR_DISCORD_CDN_URL, PATH);

        cached = BA_String_Copy(*results.value);

        SBR_DISCORDCONFIGURATION_SETUP_URL("http");
    }

    SBR_DISCORDCONFIGURATION_ADD_PATH();
    return cached;
}
