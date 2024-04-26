// Copyright (c) 2024, PortalPlayer <email@portalplayer.xyz>
// Licensed under MIT <https://opensource.org/licenses/MIT>

#include <BaconAPI/Debugging/StaticAssert.h>
#include <BaconAPI/Logger.h>
#include <BaconAPI/Debugging/Assert.h>
#include <Threads/Heartbeat.h>

#include "Discord/Gateway/Events.h"
#include "Token.h"
#include "UserAgent.h"
#include "Discord/Gateway/Gateway.h"

#define SBR_GATEWAYEVENTS_CREATE_EVENT_FUNCTION_HEADER(name) static void SBR_GatewayEvents_Action ## name(const json_object* data)
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
    SBR_GATEWAYEVENTS_CREATE_ENTRY(SBR_GATEWAYEVENT_CODE_HEARTBEAT_ACKNOWLEDGE, BA_BOOLEAN_FALSE, BA_BOOLEAN_TRUE),
};

BA_STATIC_ASSERT_LOOKUP_TABLE_CHECK(sbrGatewayEvents, SBR_GATEWAYEVENT_CODE_SIZE);

const SBR_GatewayEvents_Information* SBR_GatewayEvents_Get(SBR_GatewayEvent_Codes operationCode) {
    return &sbrGatewayEvents[operationCode];
}

SBR_GATEWAYEVENTS_CREATE_EVENT_FUNCTION_HEADER(SBR_GATEWAYEVENT_CODE_DISPATCH) {
    BA_LOGGER_WARN("Stub\n");
}

SBR_GATEWAYEVENTS_CREATE_EVENT_FUNCTION_HEADER(SBR_GATEWAYEVENT_CODE_HEARTBEAT) {
    BA_LOGGER_WARN("Requested heartbeat\n");
    SBR_HeartbeatThread_Pause(BA_BOOLEAN_TRUE);
    SBR_GATEWAY_SEND_AND_FREE(SBR_GatewayEvents_CreateHeartbeat());
}

SBR_GATEWAYEVENTS_CREATE_EVENT_FUNCTION_HEADER(SBR_GATEWAYEVENT_CODE_RECONNECT) {
    BA_LOGGER_WARN("Stub\n");
}

SBR_GATEWAYEVENTS_CREATE_EVENT_FUNCTION_HEADER(SBR_GATEWAYEVENT_CODE_INVALID_SESSION) {
    BA_LOGGER_WARN("Stub\n");
}

SBR_GATEWAYEVENTS_CREATE_EVENT_FUNCTION_HEADER(SBR_GATEWAYEVENT_CODE_HELLO) {
    BA_LOGGER_TRACE("Discord said hello\n");

    json_object* interval = json_object_object_get(data, "heartbeat_interval");

    BA_ASSERT(interval != NULL, "Malformed packet: missing JSON field\n");
    SBR_Gateway_SetInterval(json_object_get_int(interval));
    SBR_HeartbeatThread_Pause(BA_BOOLEAN_FALSE);
    SBR_GATEWAY_SEND_AND_FREE(SBR_GatewayEvents_CreateIdentify());
}

SBR_GATEWAYEVENTS_CREATE_EVENT_FUNCTION_HEADER(SBR_GATEWAYEVENT_CODE_HEARTBEAT_ACKNOWLEDGE) {
    // TODO: Unmark cURL connection as "cold"
    BA_LOGGER_TRACE("Heartbeat acknowledged\n");
    SBR_HeartbeatThread_Pause(BA_BOOLEAN_FALSE);
}

SBR_GatewayEvent* SBR_GatewayEvents_CreateHeartbeat(void) {
    return SBR_GatewayEvent_Create(SBR_GATEWAYEVENT_CODE_HEARTBEAT, 0, "");
}

SBR_GatewayEvent* SBR_GatewayEvents_CreateIdentify(void) {
    SBR_GatewayEvent* event = SBR_GatewayEvent_Create(SBR_GATEWAYEVENT_CODE_IDENTIFY, 0, "");
    json_object* properties = json_object_new_object();

    BA_ASSERT(properties != NULL, "Failed to create JSON properties\n");
    
    int errors = json_object_object_add(properties, "os", json_object_new_string(BA_OPERATINGSYSTEM_NAME));
    
    errors = !errors && json_object_object_add(properties, "browser", json_object_new_string(SBR_UserAgent_Get()));
    errors = !errors && json_object_object_add(properties, "device", json_object_new_string(SBR_UserAgent_Get()));
    errors = !errors && json_object_object_add(event->data, "token", json_object_new_string(SBR_Token_Get()));
    errors = !errors && json_object_object_add(event->data, "properties", properties);
    errors = !errors && json_object_object_add(event->data, "intents", json_object_new_int(0));

    BA_ASSERT(!errors, "Failed to initialize JSON\n");
    return event;
}