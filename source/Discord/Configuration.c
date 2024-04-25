// Copyright (c) 2024, PortalPlayer <email@portalplayer.xyz>
// Licensed under MIT <https://opensource.org/licenses/MIT>

#include <BaconAPI/Internal/Boolean.h>
#include <BaconAPI/Number.h>
#include <BaconAPI/ArgumentHandler.h>
#include <BaconAPI/String.h>

#include "Discord/Configuration.h"
#include "BuiltInArguments.h"

#define SBR_DISCORDCONFIGURATION_HACK_STRING2(string) #string
#define SBR_DISCORDCONFIGURATION_HACK_STRING1(string) SBR_DISCORDCONFIGURATION_HACK_STRING2(string)

#define SBR_DISCORDCONFIGURATION_SETUP_STRING(argument, short, default) \
initialized = BA_BOOLEAN_TRUE;                                          \
BA_ArgumentHandler_ShortResults results;                                \
if (BA_ArgumentHandler_GetInformationWithShort(argument, short, BA_BOOLEAN_FALSE, &results) == 0) { \
    cached = default;                                                   \
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
    static const char* cached = SBR_DISCORD_ROOT_URL;
    static BA_Boolean initialized = BA_BOOLEAN_FALSE;

    if (!initialized) {
        SBR_DISCORDCONFIGURATION_SETUP_STRING(SBR_BUILTINARGUMENTS_DISCORD_API_ROOT, SBR_BUILTINARGUMENTS_DISCORD_API_ROOT_SHORT, SBR_DISCORD_ROOT_URL);
        
        cached = *results.value;
    }

    return cached;
}

const char* SBR_DiscordConfiguration_GetAPIURL(void) {
    static const char* cached = NULL;

    if (cached == NULL) {
        if (!BA_ArgumentHandler_ContainsArgumentOrShort(SBR_BUILTINARGUMENTS_DISCORD_API, SBR_BUILTINARGUMENTS_DISCORD_API_SHORT, BA_BOOLEAN_FALSE) && !BA_ArgumentHandler_ContainsArgumentOrShort(SBR_BUILTINARGUMENTS_DISCORD_API_ROOT, SBR_BUILTINARGUMENTS_DISCORD_API_ROOT_SHORT, BA_BOOLEAN_FALSE)) {
            cached = SBR_DISCORD_API_URL;
            return cached;
        }
        
        cached = BA_String_Copy(SBR_DiscordConfiguration_GetAPIRootURL());
        
        SBR_DISCORDCONFIGURATION_SETUP_URL("http");
        BA_String_Append(&cached, "api/v%i");
        BA_String_Format(&cached, SBR_DiscordConfiguration_GetAPIVersion());
    }

    return cached;
}

const char* SBR_DiscordConfiguration_GetWebSocketURL(void) {
    static const char* cached = SBR_DISCORD_ROOT_URL;
    static BA_Boolean initialized = BA_BOOLEAN_FALSE;

    if (!initialized) {
        SBR_DISCORDCONFIGURATION_SETUP_STRING(SBR_BUILTINARGUMENTS_DISCORD_WEBSOCKET, SBR_BUILTINARGUMENTS_DISCORD_WEBSOCKET_SHORT, SBR_DISCORD_WEBSOCKET_URL);

        cached = BA_String_Copy(*results.value);

        SBR_DISCORDCONFIGURATION_SETUP_URL("ws");
    }

    return cached;
}

const char* SBR_DiscordConfiguration_GetCDNURL(void) {
    static const char* cached = SBR_DISCORD_ROOT_URL;
    static BA_Boolean initialized = BA_BOOLEAN_FALSE;

    if (!initialized) {
        SBR_DISCORDCONFIGURATION_SETUP_STRING(SBR_BUILTINARGUMENTS_DISCORD_CDN, SBR_BUILTINARGUMENTS_DISCORD_CDN_SHORT, SBR_DISCORD_CDN_URL);

        cached = BA_String_Copy(*results.value);

        SBR_DISCORDCONFIGURATION_SETUP_URL("http");
    }

    return cached;
}
