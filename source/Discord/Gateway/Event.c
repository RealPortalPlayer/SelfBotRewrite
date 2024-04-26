// Copyright (c) 2024, PortalPlayer <email@portalplayer.xyz>
// Licensed under MIT <https://opensource.org/licenses/MIT>

#include <stdlib.h>
#include <BaconAPI/Debugging/Assert.h>
#include <WebSocket/cURL.h>
#include <string.h>

#include "Discord/Gateway/Event.h"

BA_Boolean SBR_GatewayEvent_CanReceiveCode(SBR_GatewayEvent_Codes code) {
    return SBR_GatewayEvent_IsCodeValid(code) &&
           (code == SBR_GATEWAYEVENT_CODE_DISPATCH ||
           code == SBR_GATEWAYEVENT_CODE_HEARTBEAT ||
           code == SBR_GATEWAYEVENT_CODE_RECONNECT ||
           code >= SBR_GATEWAYEVENT_CODE_INVALID_SESSION);
}

BA_Boolean SBR_GatewayEvent_CanSendCode(SBR_GatewayEvent_Codes code) {
    return SBR_GatewayEvent_IsCodeValid(code) &&
           ((code >= SBR_GATEWAYEVENT_CODE_HEARTBEAT && code <= SBR_GATEWAYEVENT_CODE_RESUME) ||
           code == SBR_GATEWAYEVENT_CODE_REQUEST_GUILD_MEMBERS);
}

BA_Boolean SBR_GatewayEvent_IsCodeValid(SBR_GatewayEvent_Codes code) {
    return code < SBR_GATEWAYEVENT_CODE_SIZE && code != 5;
}

SBR_GatewayEvent* SBR_GatewayEvent_Create(SBR_GatewayEvent_Codes code, int sequence, const char* eventName) {
    SBR_GatewayEvent* event = malloc(sizeof(SBR_GatewayEvent));

    BA_ASSERT(event != NULL, "Failed to allocate memory for Gateway event\n");

    event->operationCode = code;
    event->data = json_object_new_object();
    event->sequence = sequence;
    event->eventName = eventName;

    BA_ASSERT(event->data != NULL, "Failed to create Gateway event data\n");
    return event;
}

BA_Boolean SBR_GatewayEvent_Send(const SBR_GatewayEvent* event) {
    if (!SBR_GatewayEvent_CanSendCode(event->operationCode)) {
        BA_LOGGER_ERROR("Code is receive only: %i\n", event->operationCode);
        return BA_BOOLEAN_FALSE;
    }

    BA_LOGGER_TRACE("Sending: %i\n", event->operationCode);

    json_object* json = json_object_new_object();
    
    BA_ASSERT(json != NULL, "Failed to create JSON object\n");

    int errors = json_object_object_add(json, "op", json_object_new_int(event->operationCode));

    errors = !errors && json_object_object_add(json, "d", event->data);
    errors = !errors && json_object_object_add(json, "s", json_object_new_int(event->sequence));
    errors = !errors && json_object_object_add(json, "t", json_object_new_string(event->eventName));

    BA_ASSERT(!errors, "Failed to initialize JSON\n");

    const char* results = json_object_to_json_string(json);
    
    SBR_CURL_ASSERT(SBR_cURL_Send(results, strlen(results), NULL, CURLWS_TEXT), "Failed to send Gateway packet: %s\n");
    return BA_BOOLEAN_TRUE;
}
