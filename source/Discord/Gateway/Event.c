// Copyright (c) 2024, PortalPlayer <email@portalplayer.xyz>
// Licensed under MIT <https://opensource.org/licenses/MIT>

#include <stdlib.h>
#include <BaconAPI/Debugging/Assert.h>
#include <WebSocket/cURL.h>
#include <string.h>
#include <json_tokener.h>

#include "Discord/Gateway/Event.h"
#include "Discord/Gateway/Events.h"

// TODO: Packet queue

BA_Boolean SBR_GatewayEvent_CanReceiveCode(SBR_GatewayEvent_Codes code) {
    return SBR_GatewayEvents_Get(code)->action != NULL;
}

BA_Boolean SBR_GatewayEvent_CanSendCode(SBR_GatewayEvent_Codes code) {
    return SBR_GatewayEvents_Get(code)->supportsSending;
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

void SBR_GatewayEvent_Send(const SBR_GatewayEvent* event) {
    BA_ASSERT(SBR_GatewayEvent_CanSendCode(event->operationCode), "Code is receive only: %i\n", event->operationCode);
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
}

void SBR_GatewayEvent_Parse(const char* buffer) {
    json_object* object = json_tokener_parse(buffer);

    BA_ASSERT(object != NULL, "Failed to parse buffer: %s\n", buffer);
    
    json_object* operationCode = json_object_object_get(object, "op");
    json_object* data = json_object_object_get(object, "d");

    BA_ASSERT(operationCode != NULL && data != NULL, "Malformed packet: missing JSON fields\n");

    int parsedOperationCode = json_object_get_int(operationCode);

    BA_ASSERT(SBR_GatewayEvent_CanReceiveCode(parsedOperationCode), "Malformed packet: cannot receive code %i\n", parsedOperationCode);
    BA_LOGGER_TRACE("Received event: %i\n", parsedOperationCode);
    SBR_GatewayEvents_Get(parsedOperationCode)->action(data);
}
