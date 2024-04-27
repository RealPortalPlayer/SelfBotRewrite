// Copyright (c) 2024, PortalPlayer <email@portalplayer.xyz>
// Licensed under MIT <https://opensource.org/licenses/MIT>

#include <BaconAPI/Debugging/Assert.h>
#include <Discord/Configuration.h>
#include <BaconAPI/String.h>

#include "Discord/API/Events.h"

char* SBR_DiscordAPIEvents_GetMessagesURL(const json_object* data) {
    static char* url = NULL;
    const json_object* id = json_object_object_get(data, "id");

    if (url == NULL) {
        url = BA_String_Copy("/channels/%lu/messages");

        BA_ASSERT(url != NULL, "Failed to allocate memory for base URL\n");
    }
    
    char* clonedUrl = BA_String_Copy(url);

    BA_ASSERT(clonedUrl != NULL, "Failed to allocate memory for parsed URL\n");
    BA_ASSERT(id != NULL, "Malformed packet: missing JSON field\n");

    char* newUrl = SBR_DiscordConfiguration_GetAPIURL(BA_String_Format(&clonedUrl, json_object_get_uint64(id)));

    free(clonedUrl);
    return newUrl;
}

SBR_DiscordAPIEvents_Function SBR_DiscordAPIEvents_GetFunction(SBR_DiscordAPIEvent_Codes code) {
    switch (code) {
        case SBR_DISCORDAPIEVENT_CODE_CREATE_MESSAGE: return &SBR_DiscordAPIEvents_GetMessagesURL;
        default: BA_ASSERT_ALWAYS("Invalid code: %i\n", code);
    }
}
