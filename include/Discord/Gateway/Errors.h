// Purpose: Registered errors. Should only be used internally
// Created on: 4/26/24 @ 3:09 PM

// Copyright (c) 2024, PortalPlayer <email@portalplayer.xyz>
// Licensed under MIT <https://opensource.org/licenses/MIT>

#pragma once

#include "Error.h"

typedef void (*SBR_GatewayErrors_Action)(const char* message);

typedef struct {
    SBR_GatewayError_Codes code;
    BA_Boolean reconnectable;
    SBR_GatewayErrors_Action action;
} SBR_GatewayErrors_Information;

const SBR_GatewayErrors_Information* SBR_GatewayErrors_Get(SBR_GatewayError_Codes code);
