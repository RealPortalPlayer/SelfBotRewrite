// Copyright (c) 2024, PortalPlayer <email@portalplayer.xyz>
// Licensed under MIT <https://opensource.org/licenses/MIT>

#include <stdlib.h>
#include <BaconAPI/Debugging/Assert.h>

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
