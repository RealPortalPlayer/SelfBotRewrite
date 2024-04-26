// Copyright (c) 2024, PortalPlayer <email@portalplayer.xyz>
// Licensed under MIT <https://opensource.org/licenses/MIT>

#include <BaconAPI/Debugging/Assert.h>
#include <string.h>
#include <json_tokener.h>

#include "Discord/Gateway/Gateway.h"
#include "WebSocket/cURL.h"
#include "Discord/Gateway/Events.h"

static int sbrGatewayInterval = 0;

void SBR_Gateway_Send(const SBR_GatewayEvent* event) {
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
    
    SBR_cURL_Send(results, strlen(results), NULL, CURLWS_TEXT);
}

void SBR_Gateway_Parse(const char* buffer) {
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

int SBR_Gateway_GetInterval(void) {
    return sbrGatewayInterval;
}

void SBR_Gateway_SetInterval(int interval) {
    BA_LOGGER_DEBUG("Setting interval: %i\n", interval);

    sbrGatewayInterval = interval;
}
