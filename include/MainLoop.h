// Purpose: Main loop
// Created on: 4/26/24 @ 3:29 AM

// Copyright (c) 2024, PortalPlayer <email@portalplayer.xyz>
// Licensed under MIT <https://opensource.org/licenses/MIT>

#pragma once

#include <BaconAPI/Internal/Boolean.h>

BA_Boolean SBR_MainLoop_IsShuttingDown(void);

void SBR_MainLoop_SignalDisconnected(void);
BA_Boolean SBR_MainLoop_Start(void);
void SBR_MainLoop_Shutdown(void);
