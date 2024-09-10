// Copyright (c) 2024, PortalPlayer <email@portalplayer.xyz>
// Licensed under MIT <https://opensource.org/licenses/MIT>

#include <stdlib.h>
#include <BaconAPI/Debugging/Assert.h>

#include "Discord/Gateway/Event.h"
#include "Discord/Gateway/Events.h"
#include "Memory.h"

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
    SBR_GatewayEvent* event = BA_Memory_Allocate(sizeof(SBR_GatewayEvent), SBR_MEMORY_TYPE_GATEWAY_EVENT);
    
    event->operationCode = code;
    event->data = json_object_new_object();
    event->sequence = sequence;
    event->eventName = eventName;

    BA_ASSERT(event->data != NULL, "Failed to create Gateway event data\n");
    return event;
}

void SBR_GatewayEvent_Free(SBR_GatewayEvent* event) {
    BA_LOGGER_TRACE("Freeing: %i\n", event->operationCode);
    
    if (!json_object_put(event->data))
        BA_LOGGER_WARN("Reference count leak\n");

    BA_Memory_Deallocate(event, sizeof(SBR_GatewayEvent), SBR_MEMORY_TYPE_GATEWAY_EVENT);
}
