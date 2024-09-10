// Purpose: ISO 8601 implementation
// Created on: 9/9/24 @ 9:42 PM

// Copyright (c) 2024, PortalPlayer <email@portalplayer.xyz>
// Licensed under MIT <https://opensource.org/licenses/MIT>

#pragma once

typedef struct {
    int year;
    int month;
    int day;
    int hour;
    int minute;
    float second;
} SBR_Time;

SBR_Time* SBR_Time_Parse(const char* string);
