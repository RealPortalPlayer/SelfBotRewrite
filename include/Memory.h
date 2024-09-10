// Purpose: Memory manager
// Created on: 9/9/24 @ 11:10 PM

// Copyright (c) 2024, PortalPlayer <email@portalplayer.xyz>
// Licensed under MIT <https://opensource.org/licenses/MIT>

#pragma once

#define BA_MEMORY_INFORMATION_ENUM_NAME SBR_Memory_Type
#define BA_MEMORY_INFORMATION_ENUM_SIZE SBR_MEMORY_TYPE_SIZE

#include <BaconAPI/Memory.h>

typedef enum SBR_Memory_Type {
    SBR_MEMORY_TYPE_DYNAMIC_ARRAY,
    SBR_MEMORY_TYPE_COMMAND,
    SBR_MEMORY_TYPE_TIME,
    SBR_MEMORY_TYPE_GATEWAY_EVENT,
    SBR_MEMORY_TYPE_SNOWFLAKE,
    SBR_MEMORY_TYPE_EVENT_BUFFER,

    /**
     * Not a real type
     */
    SBR_MEMORY_TYPE_SIZE
} SBR_Memory_Type;
