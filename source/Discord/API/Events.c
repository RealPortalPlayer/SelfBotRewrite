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
SBR_DISCORDAPIEVENTS_CREATE_EVENT_FUNCTION_HEADER(SBR_DISCORDAPIEVENT_CODE_GET_CHANNEL);

static SBR_DiscordAPIEvents_Information sbrDiscordAPIEvents[] = {
    SBR_DISCORDAPIEVENTS_CREATE_ENTRY(SBR_DISCORDAPIEVENT_CODE_CREATE_MESSAGE),
    SBR_DISCORDAPIEVENTS_CREATE_ENTRY(SBR_DISCORDAPIEVENT_CODE_GET_CHANNEL)
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

SBR_DISCORDAPIEVENTS_CREATE_EVENT_FUNCTION_HEADER(SBR_DISCORDAPIEVENT_CODE_GET_CHANNEL) {
    char* url = SBR_DiscordConfiguration_GetAPIURL("channels/%lu");
    char* response = BA_String_CreateEmpty();

    SBR_cURL_HTTPSend(BA_String_Format(&url, variables->snowflake->original), "", BA_BOOLEAN_FALSE, &response);

    json_object* parsed = json_tokener_parse(response);

    if (parsed == NULL)
        BA_LOGGER_ERROR("Failed to parse respone: %s\n", response);

    free(response);
    free(url);
    return parsed;
}

SBR_DiscordMessage* SBR_DiscordAPIEvents_SendMessage(const SBR_Snowflake* id, const char* content) {
    if (content == NULL) {
        BA_LOGGER_ERROR("Message contents is null\n");
        return NULL;
    }

    if (id == NULL) {
        BA_LOGGER_ERROR("Channel ID is null\n");
        return NULL;
    }

    if (content[0] == '\0') {
        BA_LOGGER_ERROR("Message contents cannot be empty\n");
        return NULL;
    }
    
    json_object* data = json_object_new_object();

    if (data == NULL) {
        BA_LOGGER_ERROR("Failed to create send message data\n");
        return NULL;
    }

    if (json_object_object_add(data, "content", json_object_new_string(content))) {
        BA_LOGGER_ERROR("Failed to initialize JSON\n");
        json_object_put(data);
        return NULL;
    }

    SBR_DiscordAPIEvents_Variables variables = {
        .snowflake = id
    };
    json_object* response;

    SBR_DiscordAPI_Send(SBR_DISCORDAPIEVENT_CODE_CREATE_MESSAGE, data, &response, &variables);

    SBR_DiscordMessage* message = SBR_DiscordMessage_Create(response);
    
    json_object_put(response);
    return message;
}

SBR_DiscordChannel* SBR_DiscordAPIEvents_GetChannel(const SBR_Snowflake* id) {
    SBR_DiscordAPIEvents_Variables variables = {
        .snowflake = id
    };
    json_object* response;

    SBR_DiscordAPI_Send(SBR_DISCORDAPIEVENT_CODE_GET_CHANNEL, NULL, &response, &variables);

    SBR_DiscordChannel* channel = SBR_DiscordChannel_Create(response);

    json_object_put(response);
    return channel;
}
