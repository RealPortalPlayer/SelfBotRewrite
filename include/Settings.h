// Purpose: Settings manager
// Created on: 4/22/24 @ 8:30 PM

// Copyright (c) 2024, PortalPlayer <email@portalplayer.xyz>
// Licensed under MIT <https://opensource.org/licenses/MIT>

#pragma once

#include <BaconAPI/Internal/Boolean.h>

BA_Boolean SBR_Settings_Get(const char* key, char** output);

void SBR_Settings_Load(void);
