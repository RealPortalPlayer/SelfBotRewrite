// Copyright (c) 2024, PortalPlayer <email@portalplayer.xyz>
// Licensed under MIT <https://opensource.org/licenses/MIT>

#include <BaconAPI/String.h>
#include <json_object.h>

#include "Discord/Objects/Channel.h"

#include "Discord/API/API.h"

json_object* SBR_DiscordChannel_Send(const SBR_Snowflake* id, const char* content) {
    json_object* data = json_object_new_object();
    json_object* dataData = json_object_new_object();
    json_object* output;

    json_object_object_add(data, "id", json_object_new_uint64(id->original));
    json_object_object_add(dataData, "content", json_object_new_string(content));
    json_object_object_add(data, "data", dataData);
    SBR_DiscordAPI_Send(SBR_DISCORDAPIEVENT_CODE_CREATE_MESSAGE, data, &output);
    json_object_put(dataData);
    json_object_put(data);
    return output;
}
