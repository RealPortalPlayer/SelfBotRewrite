// Purpose: Memory manager
// Created on: 9/9/24 @ 11:10 PM

// Copyright (c) 2024, PortalPlayer <email@portalplayer.xyz>
// Licensed under MIT <https://opensource.org/licenses/MIT>

#pragma once

#include <stddef.h>

typedef enum {
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

typedef struct {
    size_t allocatedBytes;
    size_t allocatedAmount;
} SBR_Memory_Data;

const SBR_Memory_Data* SBR_Memory_Get(void);
size_t SBR_Memory_GetAllocatedBytes(void);
size_t SBR_Memory_GetAllocatedAmount(void);

char* SBR_Memory_GetAllocationInformation(const char* prefix);
void* SBR_Memory_Allocate(size_t size, SBR_Memory_Type memoryType);
void* SBR_Memory_Reallocate(void* pointer, size_t oldSize, size_t newSize, SBR_Memory_Type memoryType);
void SBR_Memory_Deallocate(void* pointer, size_t oldSize, SBR_Memory_Type memoryType);
void SBR_Memory_AddSize(size_t size, SBR_Memory_Type memoryType);
void SBR_Memory_RemoveSize(size_t size, SBR_Memory_Type memoryType);
