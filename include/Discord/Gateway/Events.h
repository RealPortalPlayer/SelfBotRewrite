// Purpose: Registered events. Should only be used internally
// Created on: 4/25/24 @ 11:25 PM

// Copyright (c) 2024, PortalPlayer <email@portalplayer.xyz>
// Licensed under MIT <https://opensource.org/licenses/MIT>

#pragma once

#include "Discord/Gateway/Event.h"

typedef const char* (*SBR_GatewayEvents_Action)(const json_object* data);

typedef struct {
    SBR_GatewayEvent_Codes operationCode;
    BA_Boolean supportsSending;
    SBR_GatewayEvents_Action action;
} SBR_GatewayEvents_Information;

const SBR_GatewayEvents_Information* SBR_GatewayEvents_Get(SBR_GatewayEvent_Codes operationCode);
