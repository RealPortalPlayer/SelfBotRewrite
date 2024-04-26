// Purpose: Discord gateway general implementation
// Created on: 4/26/24 @ 10:35 AM

// Copyright (c) 2024, PortalPlayer <email@portalplayer.xyz>
// Licensed under MIT <https://opensource.org/licenses/MIT>

#pragma once

#include "Event.h"

int SBR_Gateway_GetInterval(void);

/**
 * You shouldn't need to call this directly
 */
void SBR_Gateway_Send(const SBR_GatewayEvent* event);
void SBR_Gateway_Parse(const char* buffer);
void SBR_Gateway_SetInterval(int interval);