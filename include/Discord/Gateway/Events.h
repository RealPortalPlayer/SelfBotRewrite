// Purpose: Registered events. Should only be used internally
// Created on: 4/25/24 @ 11:25 PM

// Copyright (c) 2024, PortalPlayer <email@portalplayer.xyz>
// Licensed under MIT <https://opensource.org/licenses/MIT>

#pragma once

#include "Event.h"
#include "../Status.h"

typedef void (*SBR_GatewayEvents_Action)(json_object* data, int sequence, const char* eventName);

typedef struct {
    SBR_GatewayEvent_Codes operationCode;
    BA_Boolean supportsSending;
    SBR_GatewayEvents_Action action;
} SBR_GatewayEvents_Information;

const SBR_GatewayEvents_Information* SBR_GatewayEvents_Get(SBR_GatewayEvent_Codes operationCode);

SBR_GatewayEvent* SBR_GatewayEvents_CreateHeartbeat(void);
SBR_GatewayEvent* SBR_GatewayEvents_CreateIdentify(void);
SBR_GatewayEvent* SBR_GatewayEvents_CreatePresenceUpdate(SBR_DiscordStatus status, BA_Boolean afk); // TODO: Activities
// TODO: SBR_GATEWAYEVENT_CODE_VOICE_STATUS_UPDATE
SBR_GatewayEvent* SBR_GatewayEvents_CreateResume(void);