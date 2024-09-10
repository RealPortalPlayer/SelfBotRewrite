// Copyright (c) 2024, PortalPlayer <email@portalplayer.xyz>
// Licensed under MIT <https://opensource.org/licenses/MIT>

#include <BaconAPI/Debugging/StaticAssert.h>
#include <BaconAPI/String.h>
#include <BaconAPI/Debugging/Assert.h>

#include "Memory.h"

static SBR_Memory_Data sbrMemoryData[] = {
    {0, 0},
    {0, 0},
    {0, 0},
    {0, 0},
    {0, 0},
    {0, 0}
};

BA_STATIC_ASSERT_LOOKUP_TABLE_CHECK(sbrMemoryData, SBR_MEMORY_TYPE_SIZE);

static SBR_Memory_Data* SBR_Memory_GetMemoryTypeInformation(SBR_Memory_Type memoryType) {
    BA_ASSERT(memoryType < SBR_MEMORY_TYPE_SIZE, "This shouldn't happen\n");
    return &sbrMemoryData[memoryType];
}

const SBR_Memory_Data* SBR_Memory_Get(void) {
    return sbrMemoryData;
}

size_t SBR_Memory_GetAllocatedBytes(void) {
    size_t allocatedBytes = 0;

    for (int i = 0; i < SBR_MEMORY_TYPE_SIZE; i++)
        allocatedBytes += sbrMemoryData[i].allocatedBytes;

    return allocatedBytes;
}

size_t SBR_Memory_GetAllocatedAmount(void) {
    size_t finalAmount = 0;

    for (int i = 0; i < SBR_MEMORY_TYPE_SIZE; i++)
        finalAmount += sbrMemoryData[i].allocatedAmount;

    return finalAmount;
}

char* SBR_Memory_GetAllocationInformation(const char* prefix) {
    char* finalString = BA_String_Copy("%sDynamicArray: %zu allocated, %zu bytes\n"
                                       "%sCommand: %zu allocated, %zu bytes\n"
                                       "%sTime: %zu allocated, %zu bytes\n"
                                       "%sGateway Events: %zu allocated, %zu bytes\n"
                                       "%sSnowflake: %zu allocated, %zu bytes\n"
                                       "%sEvent Buffer: %zu allocated, %zu bytes");

    BA_ASSERT(finalString != NULL, "Failed to allocate memory for a string\n");

#   define SBR_MEMORY_GET_MEMORY_INFORMATION(memoryType) prefix, sbrMemoryData[memoryType].allocatedAmount, sbrMemoryData[memoryType].allocatedBytes

#   define SBR_MEMORY_ADD_INFORMATION(memoryType1, memoryType2, memoryType3) \
prefix, sbrMemoryData[memoryType1].allocatedAmount + sbrMemoryData[memoryType2].allocatedAmount + sbrMemoryData[memoryType3].allocatedAmount, sbrMemoryData[memoryType1].allocatedBytes + sbrMemoryData[memoryType2].allocatedBytes + sbrMemoryData[memoryType3].allocatedBytes, \
SBR_MEMORY_GET_MEMORY_INFORMATION(memoryType1),                              \
SBR_MEMORY_GET_MEMORY_INFORMATION(memoryType2),                              \
SBR_MEMORY_GET_MEMORY_INFORMATION(memoryType3)

    BA_ASSERT(BA_String_Format(&finalString,
                               SBR_MEMORY_GET_MEMORY_INFORMATION(SBR_MEMORY_TYPE_DYNAMIC_ARRAY),
                               SBR_MEMORY_GET_MEMORY_INFORMATION(SBR_MEMORY_TYPE_COMMAND),
                               SBR_MEMORY_GET_MEMORY_INFORMATION(SBR_MEMORY_TYPE_TIME),
                               SBR_MEMORY_GET_MEMORY_INFORMATION(SBR_MEMORY_TYPE_GATEWAY_EVENT),
                               SBR_MEMORY_GET_MEMORY_INFORMATION(SBR_MEMORY_TYPE_SNOWFLAKE),
                               SBR_MEMORY_GET_MEMORY_INFORMATION(SBR_MEMORY_TYPE_EVENT_BUFFER)) != NULL, "Failed to format string\n");
    return finalString;
}

void* SBR_Memory_Allocate(size_t size, SBR_Memory_Type memoryType) {
    void* pointer;
    SBR_Memory_Data* memoryTypeInformation = SBR_Memory_GetMemoryTypeInformation(memoryType);
    
    BA_LOGGER_TRACE("Allocating memory\n"
                    "Size: %zu\n"
                    "Type: %i\n", size, memoryType);

    BA_ASSERT(size > 0, "Size cannot be zero or below\n");
    BA_ASSERT((pointer = malloc(size)) != NULL, "Failed to allocate %zu bytes of data\n", size);

    memoryTypeInformation->allocatedBytes += size;
    memoryTypeInformation->allocatedAmount++;
    return pointer;
}

void* SBR_Memory_Reallocate(void* pointer, size_t oldSize, size_t newSize, SBR_Memory_Type memoryType) {
    void* newPointer;
    SBR_Memory_Data* memoryTypeInformation = SBR_Memory_GetMemoryTypeInformation(memoryType);

    BA_LOGGER_TRACE("Reallocating memory\n"
                    "Old Size: %zu\n"
                    "New Size: %zu\n"
                    "Type: %i\n", oldSize, newSize, memoryType);

    BA_ASSERT(pointer != NULL, "Pointer cannot be null\n");
    BA_ASSERT(oldSize > 0 && newSize > 0, "Size cannot be zero or below\n");
    BA_ASSERT((newPointer = realloc(pointer, newSize)) != NULL, "Failed to reallocate %zu bytes of data\n", newSize);
    
    memoryTypeInformation->allocatedBytes = memoryTypeInformation->allocatedBytes - oldSize + newSize;
    return newPointer;
}

void SBR_Memory_Deallocate(void* pointer, size_t oldSize, SBR_Memory_Type memoryType) {
    SBR_Memory_Data* memoryTypeInformation = SBR_Memory_GetMemoryTypeInformation(memoryType);

    BA_LOGGER_TRACE("Deallocating memory\n"
                    "Size: %zu\n"
                    "Type: %i\n", oldSize, memoryType);

    BA_ASSERT(pointer != NULL, "Pointer cannot be null\n");
    BA_ASSERT(oldSize > 0, "Size cannot be zero or below\n");
    free(pointer);

    memoryTypeInformation->allocatedBytes -= oldSize;
    memoryTypeInformation->allocatedAmount--;
}

void SBR_Memory_AddSize(size_t size, SBR_Memory_Type memoryType) {
    BA_LOGGER_TRACE("Adding to allocated bytes\n"
                    "Size: %zu\n"
                    "Type: %i\n", size, memoryType);

    SBR_Memory_GetMemoryTypeInformation(memoryType)->allocatedBytes += size;
}

void SBR_Memory_RemoveSize(size_t size, SBR_Memory_Type memoryType) {
    BA_LOGGER_TRACE("Removing from allocated bytes\n"
                    "Size: %zu\n"
                    "Type: %i\n", size, memoryType);

    SBR_Memory_GetMemoryTypeInformation(memoryType)->allocatedBytes -= size;
}
