// Purpose: Heartbeat thread
// Created on: 4/26/24 @ 12:29 AM

// Copyright (c) 2024, PortalPlayer <email@portalplayer.xyz>
// Licensed under MIT <https://opensource.org/licenses/MIT>

#pragma once

#include <BaconAPI/Internal/Boolean.h>

#include "Threads/ThreadInternal.h"

SBR_THREADINTERNAL_HEADER(Heartbeat);

void SBR_HeartbeatThread_Pause(BA_Boolean pause);
