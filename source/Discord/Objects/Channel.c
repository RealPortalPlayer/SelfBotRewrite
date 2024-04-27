// Copyright (c) 2024, PortalPlayer <email@portalplayer.xyz>
// Licensed under MIT <https://opensource.org/licenses/MIT>

#include <BaconAPI/String.h>
#include <json_object.h>

#include "Discord/Objects/Channel.h"
#include "cURL.h"
#include "Discord/Configuration.h"

char* SBR_DiscordChannel_Send(const SBR_Snowflake* id, const char* content) {
    char* path = BA_String_Copy("/channels/%lu/messages"); // HACK: This shouldn't need to be allocated
    json_object* data = json_object_new_object();
    char* response = BA_String_CreateEmpty();
    
    json_object_object_add(data, "content", json_object_new_string(content));
    BA_ASSERT(path != NULL, "Failed to allocate memory for API path\n");
    BA_ASSERT(response != NULL, "Failed to allocate memory for API response\n");
    SBR_cURL_HTTPSend(SBR_DiscordConfiguration_GetAPIURL(BA_String_Format(&path, id->original)), json_object_to_json_string(data), BA_BOOLEAN_TRUE, &response);
    return response;
}
