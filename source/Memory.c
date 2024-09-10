// Copyright (c) 2024, PortalPlayer <email@portalplayer.xyz>
// Licensed under MIT <https://opensource.org/licenses/MIT>

#include <BaconAPI/Debugging/StaticAssert.h>
#include <BaconAPI/String.h>
#include <BaconAPI/Debugging/Assert.h>

#include "Memory.h"

BA_Memory_TypeData baMemoryLookupTable[] = {
    {0, 0},
    {0, 0},
    {0, 0},
    {0, 0},
    {0, 0},
    {0, 0}
};

BA_STATIC_ASSERT_LOOKUP_TABLE_CHECK(baMemoryLookupTable, SBR_MEMORY_TYPE_SIZE);

char* BA_Memory_GetAllocatedInformation(const char* prefix) {
    char* finalString;

    BA_MEMORY_CREATE_INFORMATION_STRING(finalString, BA_MEMORY_DEFINE_INFORMATION_STRING_TEMPLATE("DynamicArray") "\n"
                                                     BA_MEMORY_DEFINE_INFORMATION_STRING_TEMPLATE("Command") "\n"
                                                     BA_MEMORY_DEFINE_INFORMATION_STRING_TEMPLATE("Time") "\n"
                                                     BA_MEMORY_DEFINE_INFORMATION_STRING_TEMPLATE("Snowflake") "\n"
                                                     BA_MEMORY_DEFINE_INFORMATION_STRING_TEMPLATE("Event Buffer"));
    BA_MEMORY_FORMAT_INFORMATION_STRING(finalString,
                                        BA_MEMORY_GET_MEMORY_INFORMATION(SBR_MEMORY_TYPE_DYNAMIC_ARRAY),
                                        BA_MEMORY_GET_MEMORY_INFORMATION(SBR_MEMORY_TYPE_COMMAND),
                                        BA_MEMORY_GET_MEMORY_INFORMATION(SBR_MEMORY_TYPE_TIME),
                                        BA_MEMORY_GET_MEMORY_INFORMATION(SBR_MEMORY_TYPE_GATEWAY_EVENT),
                                        BA_MEMORY_GET_MEMORY_INFORMATION(SBR_MEMORY_TYPE_SNOWFLAKE),
                                        BA_MEMORY_GET_MEMORY_INFORMATION(SBR_MEMORY_TYPE_EVENT_BUFFER));
    return finalString;
}
