// Purpose: ISO 8601 implementation
// Created on: 9/9/24 @ 9:42 PM

// Copyright (c) 2024, PortalPlayer <email@portalplayer.xyz>
// Licensed under MIT <https://opensource.org/licenses/MIT>

#pragma once

#include <BaconAPI/OperatingSystem.h>

#if BA_OPERATINGSYSTEM_WINDOWS
#   include <Windows.h>
#endif

#include <time.h>

struct tm* SBR_Time_Parse(const char* string);
const char* SBR_Time_GetMonthName(const struct tm* time);
const char* SBR_Time_GetDayName(const struct tm* time);

void SBR_Time_Deallocate(struct tm* time);
