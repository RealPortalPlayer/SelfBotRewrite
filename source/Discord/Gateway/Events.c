// Copyright (c) 2024, PortalPlayer <email@portalplayer.xyz>
// Licensed under MIT <https://opensource.org/licenses/MIT>

#include <BaconAPI/Debugging/StaticAssert.h>
#include <BaconAPI/Logger.h>
#include <BaconAPI/Debugging/Assert.h>

#include "Discord/Gateway/Events.h"

#define SBR_GATEWAYEVENTS_CREATE_EVENT_FUNCTION_HEADER(name) static const char* SBR_GatewayEvents_Action ## name(const json_object* data)
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
    BA_LOGGER_WARN("Stub\n");
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
    SBR_GatewayEvent_SetInterval(json_object_get_int(interval));
}

SBR_GATEWAYEVENTS_CREATE_EVENT_FUNCTION_HEADER(SBR_GATEWAYEVENT_CODE_HEARTBEAT_ACKNOWLEDGE) {
    // TODO: Unmark cURL connection as "cold"
    BA_LOGGER_TRACE("Heartbeat acknowledged\n");
    BA_LOGGER_WARN("Stub\n");
}
