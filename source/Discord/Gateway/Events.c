// Copyright (c) 2024, PortalPlayer <email@portalplayer.xyz>
// Licensed under MIT <https://opensource.org/licenses/MIT>

#include <BaconAPI/Debugging/StaticAssert.h>
#include <BaconAPI/Logger.h>
#include <BaconAPI/Debugging/Assert.h>
#include <BaconAPI/String.h>
#include <BaconAPI/Math/Bitwise.h>

#include "Discord/Gateway/Events.h"

#include <cURL.h>

#include "Token.h"
#include "UserAgent.h"
#include "Discord/Gateway/Gateway.h"
#include "MainLoop.h"
#include "Threads/Heartbeat.h"
#include "Bot.h"

#define SBR_GATEWAYEVENTS_CREATE_EVENT_FUNCTION_HEADER(name) static void SBR_GatewayEvents_Action ## name(const json_object* data, int sequence, const char* eventName)
#define SBR_GATEWAYEVENTS_CREATE_ENTRY_BA_BOOLEAN_TRUE(code, allowSending) \
{                                                                           \
    code,                                                                   \
    allowSending,                                                           \
    SBR_GatewayEvents_Action ## code                                        \
}

#define SBR_GATEWAYEVENTS_CREATE_ENTRY_BA_BOOLEAN_FALSE(code, allowSending) \
{                                                                           \
    code,                                                                   \
    BA_BOOLEAN_TRUE,                                                        \
    NULL                                                                    \
}

#define SBR_GATEWAYEVENTS_CREATE_ENTRY(code, allowSending, allowReceiving) SBR_GATEWAYEVENTS_CREATE_ENTRY_ ## allowReceiving (code, allowSending)

#define SBR_GATEWAYEVENTS_STUB_ENTRY {0, BA_BOOLEAN_FALSE, NULL}

#define SBR_GATEWAYEVENTS_ENFORCE_DATA() \
if (data == NULL) {                      \
    BA_LOGGER_ERROR("Malformed packet: missing JSON field\n"); \
    SBR_MainLoop_SignalDisconnected();   \
    return;                              \
}

#define SBR_GATEWAYEVENTS_STUB_FUNCTION(code) \
SBR_GATEWAYEVENTS_CREATE_EVENT_FUNCTION_HEADER(code) { \
    BA_LOGGER_WARN("Stub: " #code "\n");      \
}

SBR_GATEWAYEVENTS_CREATE_EVENT_FUNCTION_HEADER(SBR_GATEWAYEVENT_CODE_DISPATCH);
SBR_GATEWAYEVENTS_CREATE_EVENT_FUNCTION_HEADER(SBR_GATEWAYEVENT_CODE_HEARTBEAT);
SBR_GATEWAYEVENTS_CREATE_EVENT_FUNCTION_HEADER(SBR_GATEWAYEVENT_CODE_RECONNECT);
SBR_GATEWAYEVENTS_CREATE_EVENT_FUNCTION_HEADER(SBR_GATEWAYEVENT_CODE_INVALID_SESSION);
SBR_GATEWAYEVENTS_CREATE_EVENT_FUNCTION_HEADER(SBR_GATEWAYEVENT_CODE_HELLO);
SBR_GATEWAYEVENTS_CREATE_EVENT_FUNCTION_HEADER(SBR_GATEWAYEVENT_CODE_HEARTBEAT_ACKNOWLEDGE);

static SBR_GatewayEvents_Information sbrGatewayEvents[] = {
    SBR_GATEWAYEVENTS_CREATE_ENTRY(SBR_GATEWAYEVENT_CODE_DISPATCH, BA_BOOLEAN_FALSE, BA_BOOLEAN_TRUE),
    SBR_GATEWAYEVENTS_CREATE_ENTRY(SBR_GATEWAYEVENT_CODE_HEARTBEAT, BA_BOOLEAN_TRUE, BA_BOOLEAN_TRUE),
    SBR_GATEWAYEVENTS_CREATE_ENTRY(SBR_GATEWAYEVENT_CODE_IDENTIFY, BA_BOOLEAN_TRUE, BA_BOOLEAN_FALSE),
    SBR_GATEWAYEVENTS_CREATE_ENTRY(SBR_GATEWAYEVENT_CODE_PRESENCE_UPDATE, BA_BOOLEAN_TRUE, BA_BOOLEAN_FALSE),
    SBR_GATEWAYEVENTS_CREATE_ENTRY(SBR_GATEWAYEVENT_CODE_VOICE_STATUS_UPDATE, BA_BOOLEAN_TRUE, BA_BOOLEAN_FALSE),
    SBR_GATEWAYEVENTS_STUB_ENTRY,
    SBR_GATEWAYEVENTS_CREATE_ENTRY(SBR_GATEWAYEVENT_CODE_RESUME, BA_BOOLEAN_TRUE, BA_BOOLEAN_FALSE),
    SBR_GATEWAYEVENTS_CREATE_ENTRY(SBR_GATEWAYEVENT_CODE_RECONNECT, BA_BOOLEAN_FALSE, BA_BOOLEAN_TRUE),
    SBR_GATEWAYEVENTS_CREATE_ENTRY(SBR_GATEWAYEVENT_CODE_REQUEST_GUILD_MEMBERS, BA_BOOLEAN_TRUE, BA_BOOLEAN_FALSE),
    SBR_GATEWAYEVENTS_CREATE_ENTRY(SBR_GATEWAYEVENT_CODE_INVALID_SESSION, BA_BOOLEAN_FALSE, BA_BOOLEAN_TRUE),
    SBR_GATEWAYEVENTS_CREATE_ENTRY(SBR_GATEWAYEVENT_CODE_HELLO, BA_BOOLEAN_FALSE, BA_BOOLEAN_TRUE),
    SBR_GATEWAYEVENTS_CREATE_ENTRY(SBR_GATEWAYEVENT_CODE_HEARTBEAT_ACKNOWLEDGE, BA_BOOLEAN_FALSE, BA_BOOLEAN_TRUE)
};

BA_STATIC_ASSERT_LOOKUP_TABLE_CHECK(sbrGatewayEvents, SBR_GATEWAYEVENT_CODE_SIZE);

const SBR_GatewayEvents_Information* SBR_GatewayEvents_Get(SBR_GatewayEvent_Codes operationCode) {
    for (int index = 0; index < SBR_GATEWAYEVENT_CODE_SIZE; index++) {
        if (sbrGatewayEvents[index].operationCode != operationCode)
            continue;

        return &sbrGatewayEvents[index];
    }

    return NULL;
}

SBR_GATEWAYEVENTS_CREATE_EVENT_FUNCTION_HEADER(SBR_GATEWAYEVENT_CODE_DISPATCH) {
    SBR_GATEWAYEVENTS_ENFORCE_DATA();

    if (BA_String_Equals(eventName, "RESUMED", BA_BOOLEAN_FALSE)) {
        BA_LOGGER_DEBUG("Successfully reconnected and resumed\n");
        return;
    }
    
    if (BA_String_Equals(eventName, "READY", BA_BOOLEAN_FALSE)) {
        // TODO: API version
        json_object* user = json_object_object_get(data, "user");
        json_object* sessionId = json_object_object_get(data, "session_id");
        json_object* resumeGatewayUrl = json_object_object_get(data, "resume_gateway_url");

        if (user == NULL) {
            BA_LOGGER_ERROR("Malformed packet: missing JSON field\n");
            SBR_MainLoop_SignalDisconnected();
            return;
        }
        
        SBR_Bot_Set(SBR_DiscordUser_Create(user));
        BA_LOGGER_INFO("Bot is ready: %s#%s\n", SBR_Bot_Get()->username, SBR_Bot_Get()->discriminator);

        if (!BA_BITWISE_IS_BIT_SET(SBR_Bot_Get()->customFlags, SBR_DISCORDUSER_CUSTOM_FLAG_BOT))
            BA_LOGGER_WARN("\"Bot\" user is not actually a bot. Self-bots are against Discords TOS\n");
        
        SBR_Gateway_SetResumeData(json_object_get_string(resumeGatewayUrl), json_object_get_string(sessionId));
        BA_LOGGER_TRACE("Resume URL: %s\n"
                        "Session ID: %s\n", SBR_Gateway_GetResumeURL(), SBR_Gateway_GetSessionID());
        return;
    }
    
    BA_LOGGER_WARN("Dispatch stub: %s\n", eventName);
}

SBR_GATEWAYEVENTS_CREATE_EVENT_FUNCTION_HEADER(SBR_GATEWAYEVENT_CODE_HEARTBEAT) {
    BA_LOGGER_WARN("Requested heartbeat\n");
    SBR_HeartbeatThread_Pause(BA_BOOLEAN_TRUE);
    SBR_GATEWAY_SEND_AND_FREE(SBR_GatewayEvents_CreateHeartbeat());
}

SBR_GATEWAYEVENTS_STUB_FUNCTION(SBR_GATEWAYEVENT_CODE_RECONNECT)

SBR_GATEWAYEVENTS_CREATE_EVENT_FUNCTION_HEADER(SBR_GATEWAYEVENT_CODE_INVALID_SESSION) {
    BA_LOGGER_ERROR("Invalidated session\n");

    if (json_object_get_boolean(data)) {
        BA_LOGGER_WARN("Can reconnect (rare)\n");
        return;
    }

    SBR_MainLoop_SignalDisconnected();
}

SBR_GATEWAYEVENTS_CREATE_EVENT_FUNCTION_HEADER(SBR_GATEWAYEVENT_CODE_HELLO) {
    SBR_GATEWAYEVENTS_ENFORCE_DATA();
    BA_LOGGER_TRACE("Discord said hello\n");

    json_object* interval = json_object_object_get(data, "heartbeat_interval");
    static BA_Boolean alreadySentIdentity = BA_BOOLEAN_FALSE;

    BA_ASSERT(interval != NULL, "Malformed packet: missing JSON field\n");
    SBR_Gateway_SetInterval(json_object_get_int(interval));
    SBR_HeartbeatThread_Pause(BA_BOOLEAN_FALSE);

    if (alreadySentIdentity)
        return;

    alreadySentIdentity = BA_BOOLEAN_TRUE;

    SBR_GATEWAY_SEND_AND_FREE(SBR_GatewayEvents_CreateIdentify());
}

SBR_GATEWAYEVENTS_CREATE_EVENT_FUNCTION_HEADER(SBR_GATEWAYEVENT_CODE_HEARTBEAT_ACKNOWLEDGE) {
    // TODO: Unmark cURL connection as "cold"
    BA_LOGGER_TRACE("Heartbeat acknowledged\n");
    SBR_HeartbeatThread_Pause(BA_BOOLEAN_FALSE);
}

#define SBR_GATEWAYEVENTS_CREATOR_START_NO_PROPERTIES(code, sequence, eventName) \
SBR_GatewayEvent* event = SBR_GatewayEvent_Create(code, sequence, eventName); \
BA_Boolean errors = BA_BOOLEAN_FALSE

#define SBR_GATEWAYEVENTS_CREATOR_START(code, sequence, eventName) \
SBR_GATEWAYEVENTS_CREATOR_START_NO_PROPERTIES(code, sequence, eventName); \
json_object* properties = json_object_new_object();                \
BA_ASSERT(properties != NULL, "Failed to create JSON properties\n") \


#define SBR_GATEWAYEVENTS_JSON_ADD(json, key, value) errors = !errors && json_object_object_add(json, key, value)

#define SBR_GATEWAYEVENTS_CREATOR_END() \
BA_ASSERT(!errors, "Failed to initialize JSON\n"); \
return event

SBR_GatewayEvent* SBR_GatewayEvents_CreateHeartbeat(void) {
    return SBR_GatewayEvent_Create(SBR_GATEWAYEVENT_CODE_HEARTBEAT, 0, "");
}

SBR_GatewayEvent* SBR_GatewayEvents_CreateIdentify(void) {
    SBR_GATEWAYEVENTS_CREATOR_START(SBR_GATEWAYEVENT_CODE_IDENTIFY, 0, "");
    SBR_GATEWAYEVENTS_JSON_ADD(properties, "os", json_object_new_string(BA_OPERATINGSYSTEM_NAME));
    SBR_GATEWAYEVENTS_JSON_ADD(properties, "browser", json_object_new_string(SBR_UserAgent_Get()));
    SBR_GATEWAYEVENTS_JSON_ADD(properties, "device", json_object_new_string(SBR_UserAgent_Get()));
    SBR_GATEWAYEVENTS_JSON_ADD(event->data, "token", json_object_new_string(SBR_Token_Get()));
    SBR_GATEWAYEVENTS_JSON_ADD(event->data, "properties", properties);
    SBR_GATEWAYEVENTS_JSON_ADD(event->data, "intents", json_object_new_int(0));
    SBR_GATEWAYEVENTS_CREATOR_END();
}

SBR_GatewayEvent* SBR_GatewayEvents_CreatePresenceUpdate(SBR_DiscordStatus status, BA_Boolean afk) {
    SBR_GATEWAYEVENTS_CREATOR_START_NO_PROPERTIES(SBR_GATEWAYEVENT_CODE_PRESENCE_UPDATE, 0, "");
    SBR_GATEWAYEVENTS_JSON_ADD(event->data, "activities", json_object_new_array());
    SBR_GATEWAYEVENTS_JSON_ADD(event->data, "status", json_object_new_string(SBR_DiscordStatus_ToString(status)));
    SBR_GATEWAYEVENTS_JSON_ADD(event->data, "afk", json_object_new_boolean(afk));
    SBR_GATEWAYEVENTS_CREATOR_END();
}

SBR_GatewayEvent* SBR_GatewayEvents_CreateResume(void) {
    SBR_GATEWAYEVENTS_CREATOR_START_NO_PROPERTIES(SBR_GATEWAYEVENT_CODE_RESUME, 0, "");
    SBR_GATEWAYEVENTS_JSON_ADD(event->data, "token", json_object_new_string(SBR_Token_Get()));
    SBR_GATEWAYEVENTS_JSON_ADD(event->data, "session_id", json_object_new_string(SBR_Gateway_GetSessionID()));
    SBR_GATEWAYEVENTS_JSON_ADD(event->data, "seq", json_object_new_int(SBR_Gateway_GetLastSequence()));
    SBR_GATEWAYEVENTS_CREATOR_END();
}
