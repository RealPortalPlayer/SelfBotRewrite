// Purpose: Every registered dispatch. This really should only be used internally
// Created on: 4/28/24 @ 7:59 AM

// Copyright (c) 2024, PortalPlayer <email@portalplayer.xyz>
// Licensed under MIT <https://opensource.org/licenses/MIT>

#pragma once

#include <json_object.h>

typedef void (*SBR_GatewayDispatch_Action)(const json_object* data);

typedef struct {
    const char* code;
    SBR_GatewayDispatch_Action action;
} SBR_GatewayDispatch_Information;

const SBR_GatewayDispatch_Information* SBR_GatewayDispatch_Get(const char* code);
