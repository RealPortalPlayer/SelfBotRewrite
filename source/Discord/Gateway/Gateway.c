// Copyright (c) 2024, PortalPlayer <email@portalplayer.xyz>
// Licensed under MIT <https://opensource.org/licenses/MIT>

#include <BaconAPI/Debugging/Assert.h>
#include <string.h>
#include <json_tokener.h>
#include <BaconAPI/Thread.h>

#include "Discord/Gateway/Gateway.h"
#include "cURL.h"
#include "Discord/Gateway/Events.h"
#include "Threads/RateLimit.h"
#include "MainLoop.h"
#include "BaconAPI/String.h"
#include "Discord/Configuration.h"
#include "Discord/Gateway/Errors.h"

static int sbrGatewayInterval = 0;
static int sbrGatewayRequestCount = 0;
static char* sbrGatewayResumeUrl = NULL;
static const char* sbrGatewaySessionId;
static int sbrGatewayLastSequence;

void SBR_Gateway_Send(const SBR_GatewayEvent* event) {
    static BA_Thread_Lock threadLock;
    static BA_Boolean initialized = BA_BOOLEAN_FALSE;

    if (!initialized) {
        BA_ASSERT(BA_Thread_CreateLock(&threadLock), "Failed to create Gateway send thread lock\n");

        initialized = BA_BOOLEAN_TRUE;
    }
    
    BA_Thread_UseLock(&threadLock);

    sbrGatewayRequestCount++;
    
    BA_ASSERT(SBR_GatewayEvent_CanSendCode(event->operationCode), "Code is receive only: %i\n", event->operationCode);
    BA_LOGGER_TRACE("Sending (%i): %i\n", sbrGatewayRequestCount, event->operationCode);

    while (SBR_RateLimit_Sleeping())
        continue;

    json_object* json = json_object_new_object();
    
    BA_ASSERT(json != NULL, "Failed to create JSON object\n");

    int errors = json_object_object_add(json, "op", json_object_new_int(event->operationCode));

    errors = !errors && json_object_object_add(json, "d", event->data);
    errors = !errors && json_object_object_add(json, "s", json_object_new_int(event->sequence));
    errors = !errors && json_object_object_add(json, "t", json_object_new_string(event->eventName));

    BA_ASSERT(!errors, "Failed to initialize JSON\n");

    const char* results = json_object_to_json_string(json);
    
    SBR_cURL_WebSocketSend(results, strlen(results), NULL, CURLWS_TEXT);
    BA_Thread_Unlock(&threadLock);
}

void SBR_Gateway_Parse(const char* buffer) {
    json_object* object = json_tokener_parse(buffer);

    if (object == NULL) {
        BA_LOGGER_ERROR("Failed to parse buffer: %s\n", buffer);
        SBR_MainLoop_SignalDisconnected();
        return;
    }
    
    json_object* operationCode = json_object_object_get(object, "op");
    json_object* data = json_object_object_get(object, "d");
    json_object* sequence = json_object_object_get(object, "s");
    json_object* eventName = json_object_object_get(object, "t");

    if (operationCode == NULL) {
        BA_LOGGER_ERROR("Malformed packet: missing JSON fields\n");
        SBR_MainLoop_SignalDisconnected();
        return;
    }

    int parsedOperationCode = json_object_get_int(operationCode);

    if (!SBR_GatewayEvent_IsCodeValid(parsedOperationCode)) {
        BA_LOGGER_ERROR("Malformed packet: invalid operation code %i\n", parsedOperationCode);
        SBR_MainLoop_SignalDisconnected();
        return;
    }

    if (!SBR_GatewayEvent_CanReceiveCode(parsedOperationCode)) {
        BA_LOGGER_ERROR("Malformed packet: cannot receive code %i\n", parsedOperationCode);
        SBR_MainLoop_SignalDisconnected();
        return;
    }

    if (sequence != NULL) {
        sbrGatewayLastSequence = json_object_get_int(sequence);
        
        BA_LOGGER_TRACE("New sequence: %i\n", sbrGatewayLastSequence);
    }

    BA_LOGGER_TRACE("Received event: %i\n", parsedOperationCode);
    SBR_GatewayEvents_Get(parsedOperationCode)->action(data, json_object_get_int(sequence), json_object_get_string(eventName));
}

int SBR_Gateway_GetInterval(void) {
    return sbrGatewayInterval;
}

void SBR_Gateway_SetInterval(int interval) {
    BA_LOGGER_DEBUG("Setting interval: %i\n", interval);

    sbrGatewayInterval = interval;
}

int SBR_Gateway_GetRequestCount(void) {
    return sbrGatewayRequestCount;
}

void SBR_Gateway_ResetRequestCount(void) {
    sbrGatewayRequestCount = 0;
}

void SBR_Gateway_ParseError(uint16_t code, const char* message) {
    BA_LOGGER_TRACE("Received error: %u\n", code);

    const SBR_GatewayErrors_Information* information = SBR_GatewayErrors_Get(code);

    BA_ASSERT(information != NULL, "Unknown Discord error code (%u): %s\n", code, message);
    information->action(message);
}

const char* SBR_Gateway_GetResumeURL(void) {
    return sbrGatewayResumeUrl;
}

const char* SBR_Gateway_GetSessionID(void) {
    return sbrGatewaySessionId;
}

void SBR_Gateway_SetResumeData(const char* url, const char* id) {
    sbrGatewayResumeUrl = BA_String_Copy(url);
    sbrGatewaySessionId = id;

    BA_String_Append(&sbrGatewayResumeUrl, "?v=%i&encoding=json");
    BA_String_Format(&sbrGatewayResumeUrl, SBR_DiscordConfiguration_GetAPIVersion());
}

int SBR_Gateway_GetLastSequence(void) {
    return sbrGatewayLastSequence;
}
