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
        initialized = BA_BOOLEAN_TRUE;
        
        BA_ArgumentHandler_ShortResults results;

        if (BA_ArgumentHandler_GetInformationWithShort(SBR_BUILTINARGUMENTS_DISCORD_API_ROOT, SBR_BUILTINARGUMENTS_DISCORD_API_ROOT_SHORT, BA_BOOLEAN_FALSE, &results) == 0) {
            cached = SBR_DISCORD_ROOT_URL;
            return cached;
        }

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
        
        if (!BA_String_StartsWith(cached, "https://", BA_BOOLEAN_TRUE) && !BA_String_StartsWith(cached, "http://", BA_BOOLEAN_TRUE))
            BA_String_Prepend(&cached, "https://");

        if (!BA_String_EndsWith(cached, "/", BA_BOOLEAN_FALSE))
            BA_String_Append(&cached, "/");

        BA_String_Append(&cached, "api/v%i");
        BA_String_Format(&cached, SBR_DiscordConfiguration_GetAPIVersion());
    }

    return cached;
}

const char* SBR_DiscordConfiguration_GetWebSocketURL(void) {
    static const char* cached = SBR_DISCORD_ROOT_URL;
    static BA_Boolean initialized = BA_BOOLEAN_FALSE;

    if (!initialized) {
        initialized = BA_BOOLEAN_TRUE;
        
        BA_ArgumentHandler_ShortResults results;

        if (BA_ArgumentHandler_GetInformationWithShort(SBR_BUILTINARGUMENTS_DISCORD_WEBSOCKET, SBR_BUILTINARGUMENTS_DISCORD_WEBSOCKET_SHORT, BA_BOOLEAN_FALSE, &results) == 0) {
            cached = SBR_DISCORD_WEBSOCKET_URL;
            return cached;
        }

        cached = BA_String_Copy(*results.value);

        if (!BA_String_StartsWith(cached, "wss://", BA_BOOLEAN_TRUE) && !BA_String_StartsWith(cached, "ws://", BA_BOOLEAN_TRUE))
            BA_String_Prepend(&cached, "wss://");
    }

    return cached;
}
