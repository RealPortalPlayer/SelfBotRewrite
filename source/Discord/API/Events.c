// Copyright (c) 2024, PortalPlayer <email@portalplayer.xyz>
// Licensed under MIT <https://opensource.org/licenses/MIT>

#include <BaconAPI/String.h>
#include <BaconAPI/Debugging/StaticAssert.h>
#include <BaconAPI/Logger.h>
#include <json_tokener.h>

#include "Discord/API/Events.h"
#include "cURL.h"
#include "json_object_private.h"
#include "Discord/Configuration.h"
#include "Discord/API/API.h"

#define SBR_DISCORDAPIEVENTS_CREATE_EVENT_FUNCTION_HEADER(name) static json_object* SBR_DiscordAPIEvents_Action ## name(json_object* data, const SBR_DiscordAPIEvents_Variables* variables)
#define SBR_DISCORDAPIEVENTS_CREATE_ENTRY(code) \
{                                               \
    code,                                       \
    SBR_DiscordAPIEvents_Action ## code         \
}

SBR_DISCORDAPIEVENTS_CREATE_EVENT_FUNCTION_HEADER(SBR_DISCORDAPIEVENT_CODE_CREATE_MESSAGE);

static SBR_DiscordAPIEvents_Information sbrDiscordAPIEvents[] = {
    SBR_DISCORDAPIEVENTS_CREATE_ENTRY(SBR_DISCORDAPIEVENT_CODE_CREATE_MESSAGE)
};

BA_STATIC_ASSERT_LOOKUP_TABLE_CHECK(sbrDiscordAPIEvents, SBR_DISCORDAPIEVENT_CODE_SIZE);

const SBR_DiscordAPIEvents_Information* SBR_DiscordAPIEvents_Get(SBR_DiscordAPIEvent_Codes code) {
    for (int index = 0; index < SBR_DISCORDAPIEVENT_CODE_SIZE; index++) {
        if (sbrDiscordAPIEvents[index].code != code)
            continue;

        return &sbrDiscordAPIEvents[index];
    }

    return NULL;
}

SBR_DISCORDAPIEVENTS_CREATE_EVENT_FUNCTION_HEADER(SBR_DISCORDAPIEVENT_CODE_CREATE_MESSAGE) {
    char* url = SBR_DiscordConfiguration_GetAPIURL("channels/%lu/messages");
    char* response = BA_String_CreateEmpty();
    
    SBR_cURL_HTTPSend(BA_String_Format(&url, variables->snowflake->original), json_object_to_json_string(data), BA_BOOLEAN_TRUE, &response);

    json_object* parsed = json_tokener_parse(response);

    if (parsed == NULL)
        BA_LOGGER_ERROR("Failed to parse response: %s\n", response);

    free(response);
    free(url);
    return parsed;
}

void SBR_DiscordAPIEvents_SendMessage(const SBR_Snowflake* id, const char* content) {
    json_object* data = json_object_new_object();

    if (data == NULL) {
        BA_LOGGER_ERROR("Failed to create send message data\n");
        return;
    }

    if (json_object_object_add(data, "content", json_object_new_string(content))) {
        BA_LOGGER_ERROR("Failed to initialize JSON\n");
        json_object_put(data);
        return;
    }

    SBR_DiscordAPIEvents_Variables variables = {
        .snowflake = id
    };
    json_object* response;

    SBR_DiscordAPI_Send(SBR_DISCORDAPIEVENT_CODE_CREATE_MESSAGE, data, &response, &variables);

    // TODO: Create channel
    json_object_put(response);
}
