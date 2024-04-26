// Purpose: Discord gateway general implementation
// Created on: 4/26/24 @ 10:35 AM

// Copyright (c) 2024, PortalPlayer <email@portalplayer.xyz>
// Licensed under MIT <https://opensource.org/licenses/MIT>

#pragma once

#include "Event.h"

int SBR_Gateway_GetInterval(void);
int SBR_Gateway_GetRequestCount(void);

/**
 * You shouldn't need to call this directly
 */
void SBR_Gateway_Send(const SBR_GatewayEvent* event);
void SBR_Gateway_Parse(const char* buffer);
void SBR_Gateway_SetInterval(int interval);
void SBR_Gateway_ResetRequestCount(void);

#define SBR_GATEWAY_SEND_AND_FREE(gateway) \
do {                                       \
    SBR_GatewayEvent* createdGatewayPaddingToPreventNameCollisions = gateway; \
    SBR_Gateway_Send(createdGatewayPaddingToPreventNameCollisions); \
    SBR_GatewayEvent_Free(createdGatewayPaddingToPreventNameCollisions); \
} while (BA_BOOLEAN_FALSE)
