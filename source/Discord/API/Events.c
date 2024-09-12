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

#define SBR_DISCORDAPIEVENTS_CREATE_EVENT_DEFAULT(code, path, data, post) \
SBR_DISCORDAPIEVENTS_CREATE_EVENT_FUNCTION_HEADER(code) {                 \
    char* url = SBR_DiscordConfiguration_GetAPIURL(path);                 \
    char* response = BA_String_CreateEmpty();                             \
    SBR_cURL_HTTPSend(BA_String_Format(&url, SBR_Snowflake_ConvertToNumber(variables->snowflake)), data, post, &response); \
    json_object* parsed = json_tokener_parse(response);                   \
    if (parsed == NULL)                                                   \
        BA_LOGGER_ERROR("Failed to parse response: %s\n", response);      \
    free(response);                                                       \
    free(url);                                                            \
    return parsed;                                                        \
}
#define SBR_DISCORDAPIEVENTS_CREATE_GETTER_DEFAULT(returnType, type, code, parseFunction) \
returnType SBR_DiscordAPIEvents_Get ## type(const SBR_Snowflake* id) {                    \
    SBR_DiscordAPIEvents_Variables variables = {                                          \
        .snowflake = id                                                                   \
    };                                                                                    \
    json_object* response;                                                                \
    SBR_DiscordAPI_Send(code, NULL, &response, &variables);                               \
    returnType parsed = parseFunction(response);                                          \
    json_object_put(response);                                                            \
    return parsed;                                                                        \
}

SBR_DISCORDAPIEVENTS_CREATE_EVENT_FUNCTION_HEADER(SBR_DISCORDAPIEVENT_CODE_CREATE_MESSAGE);
SBR_DISCORDAPIEVENTS_CREATE_EVENT_FUNCTION_HEADER(SBR_DISCORDAPIEVENT_CODE_GET_CHANNEL);
SBR_DISCORDAPIEVENTS_CREATE_EVENT_FUNCTION_HEADER(SBR_DISCORDAPIEVENT_CODE_GET_GUILD);
SBR_DISCORDAPIEVENTS_CREATE_EVENT_FUNCTION_HEADER(SBR_DISCORDAPIEVENT_CODE_GET_USER);

static SBR_DiscordAPIEvents_Information sbrDiscordAPIEvents[] = {
    SBR_DISCORDAPIEVENTS_CREATE_ENTRY(SBR_DISCORDAPIEVENT_CODE_CREATE_MESSAGE),
    SBR_DISCORDAPIEVENTS_CREATE_ENTRY(SBR_DISCORDAPIEVENT_CODE_GET_CHANNEL),
    SBR_DISCORDAPIEVENTS_CREATE_ENTRY(SBR_DISCORDAPIEVENT_CODE_GET_GUILD),
    SBR_DISCORDAPIEVENTS_CREATE_ENTRY(SBR_DISCORDAPIEVENT_CODE_GET_USER),
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

SBR_DISCORDAPIEVENTS_CREATE_EVENT_DEFAULT(SBR_DISCORDAPIEVENT_CODE_CREATE_MESSAGE, "channels/%llu/messages", json_object_to_json_string(data), BA_BOOLEAN_TRUE)
SBR_DISCORDAPIEVENTS_CREATE_EVENT_DEFAULT(SBR_DISCORDAPIEVENT_CODE_GET_CHANNEL, "channels/%llu", "", BA_BOOLEAN_FALSE)
SBR_DISCORDAPIEVENTS_CREATE_EVENT_DEFAULT(SBR_DISCORDAPIEVENT_CODE_GET_GUILD, "guilds/%llu", "", BA_BOOLEAN_FALSE)
SBR_DISCORDAPIEVENTS_CREATE_EVENT_DEFAULT(SBR_DISCORDAPIEVENT_CODE_GET_USER, "users/%llu", "", BA_BOOLEAN_FALSE)

SBR_DiscordMessage* SBR_DiscordAPIEvents_SendMessage(const SBR_Snowflake* id, const char* content, SBR_EmbedCreator_Embed* embed) {
    if (content == NULL) {
        BA_LOGGER_ERROR("Message contents is null\n");
        return NULL;
    }

    if (id == NULL) {
        BA_LOGGER_ERROR("Channel ID is null\n");
        return NULL;
    }

#define SBR_DISCORDEVENTS_IS_NULL_OR_EMPTY(parameter) (embed->parameter == NULL || embed->parameter[0] == '\0')
#define SBR_DISCORDEVENTS_MEDIA_IS_NULL_OR_EMPTY(parameter) SBR_DISCORDEVENTS_IS_NULL_OR_EMPTY(parameter.url) && SBR_DISCORDEVENTS_IS_NULL_OR_EMPTY(parameter.proxyUrl)
    if (content[0] == '\0' &&
        (embed == NULL ||
            (SBR_DISCORDEVENTS_IS_NULL_OR_EMPTY(title) &&
             SBR_DISCORDEVENTS_IS_NULL_OR_EMPTY(description) &&
             SBR_DISCORDEVENTS_MEDIA_IS_NULL_OR_EMPTY(image) &&
             SBR_DISCORDEVENTS_MEDIA_IS_NULL_OR_EMPTY(thumbnail) &&
             SBR_DISCORDEVENTS_MEDIA_IS_NULL_OR_EMPTY(video) &&
             SBR_DISCORDEVENTS_IS_NULL_OR_EMPTY(provider.name) &&
             SBR_DISCORDEVENTS_IS_NULL_OR_EMPTY(provider.url) &&
             SBR_DISCORDEVENTS_IS_NULL_OR_EMPTY(author.name) &&
             SBR_DISCORDEVENTS_IS_NULL_OR_EMPTY(author.url) &&
             SBR_DISCORDEVENTS_IS_NULL_OR_EMPTY(author.iconUrl) &&
             SBR_DISCORDEVENTS_IS_NULL_OR_EMPTY(author.proxyIconUrl) &&
             embed->fields.used == 0))) {
        BA_LOGGER_ERROR("Message contents cannot be empty\n");
        return NULL;
    }
#undef SBR_DISCORDEVENTS_MEDIA_IS_NULL_OR_EMPTY
#undef SBR_DISCORDEVENTS_IS_NULL_OR_EMPTY
    
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
    json_object* parsedEmbed = NULL;
    json_object* embedArray = json_object_new_array();
    
    if (embed != NULL && embedArray != NULL) {
        parsedEmbed = SBR_EmbedCreator_Build(embed);

        if (json_object_array_add(embedArray, parsedEmbed) || json_object_object_add(data, "embeds", embedArray))
            BA_LOGGER_ERROR("Failed to add embeds to JSON\n");
    }

    SBR_DiscordAPI_Send(SBR_DISCORDAPIEVENT_CODE_CREATE_MESSAGE, data, &response, &variables);

    SBR_DiscordMessage* message = SBR_DiscordMessage_Create(response);
    
    json_object_put(response);
    return message;
}

SBR_DISCORDAPIEVENTS_CREATE_GETTER_DEFAULT(SBR_DiscordChannel*, Channel, SBR_DISCORDAPIEVENT_CODE_GET_CHANNEL, SBR_DiscordChannel_Create)
SBR_DISCORDAPIEVENTS_CREATE_GETTER_DEFAULT(SBR_DiscordGuild*, Guild, SBR_DISCORDAPIEVENT_CODE_GET_GUILD, SBR_DiscordGuild_Create)
SBR_DISCORDAPIEVENTS_CREATE_GETTER_DEFAULT(SBR_DiscordUser*, User, SBR_DISCORDAPIEVENT_CODE_GET_USER, SBR_DiscordUser_Create)