// Copyright (c) 2024, PortalPlayer <email@portalplayer.xyz>
// Licensed under MIT <https://opensource.org/licenses/MIT>

#include <BaconAPI/Debugging/StaticAssert.h>
#include <BaconAPI/String.h>
#include <BaconAPI/Memory.h>

#include "Memory.h"

BA_Memory_TypeData baMemoryLookupTable[] = {
    {0, 0},
    {0, 0},
    {0, 0},
    {0, 0},
    {0, 0},
    {0, 0},
    {0, 0},
    {0, 0},
    {0, 0},
    {0, 0},
    {0, 0},
    {0, 0},
    {0, 0}
};

BA_STATIC_ASSERT_LOOKUP_TABLE_CHECK(baMemoryLookupTable, SBR_MEMORY_TYPE_SIZE);

size_t BA_Memory_GetEnumeratorSize(void) {
    return SBR_MEMORY_TYPE_SIZE;
}

char* BA_Memory_GetAllocatedInformation(const char* prefix) {
    char* finalString;
    
    BA_MEMORY_CREATE_INFORMATION_STRING(finalString, BA_MEMORY_DEFINE_INFORMATION_STRING_TEMPLATE("DynamicArray") "\n"
                                                     BA_MEMORY_DEFINE_INFORMATION_STRING_TEMPLATE("Command") "\n"
                                                     BA_MEMORY_DEFINE_INFORMATION_STRING_TEMPLATE("Time") "\n"
                                                     BA_MEMORY_DEFINE_INFORMATION_STRING_TEMPLATE("Gateway event") "\n"
                                                     BA_MEMORY_DEFINE_INFORMATION_STRING_TEMPLATE("Event buffer") "\n"
                                                     BA_MEMORY_DEFINE_INFORMATION_STRING_TEMPLATE("Discord objects") "\n"
                                                     BA_MEMORY_DEFINE_INFORMATION_STRING_TEMPLATE("    Snowflake") "\n"
                                                     BA_MEMORY_DEFINE_INFORMATION_STRING_TEMPLATE("    Application") "\n"
                                                     BA_MEMORY_DEFINE_INFORMATION_STRING_TEMPLATE("    Channel") "\n"
                                                     BA_MEMORY_DEFINE_INFORMATION_STRING_TEMPLATE("    Emoji") "\n"
                                                     BA_MEMORY_DEFINE_INFORMATION_STRING_TEMPLATE("    Guild") "\n"
                                                     BA_MEMORY_DEFINE_INFORMATION_STRING_TEMPLATE("    Guild member") "\n"
                                                     BA_MEMORY_DEFINE_INFORMATION_STRING_TEMPLATE("    Message") "\n"
                                                     BA_MEMORY_DEFINE_INFORMATION_STRING_TEMPLATE("    User"));
    BA_MEMORY_FORMAT_INFORMATION_STRING(finalString,
                                        BA_MEMORY_GET_MEMORY_INFORMATION(SBR_MEMORY_TYPE_DYNAMIC_ARRAY),
                                        BA_MEMORY_GET_MEMORY_INFORMATION(SBR_MEMORY_TYPE_COMMAND),
                                        BA_MEMORY_GET_MEMORY_INFORMATION(SBR_MEMORY_TYPE_TIME),
                                        BA_MEMORY_GET_MEMORY_INFORMATION(SBR_MEMORY_TYPE_GATEWAY_EVENT),
                                        BA_MEMORY_GET_MEMORY_INFORMATION(SBR_MEMORY_TYPE_EVENT_BUFFER),
                                        prefix, baMemoryLookupTable[SBR_MEMORY_TYPE_SNOWFLAKE].allocatedAmount + baMemoryLookupTable[SBR_MEMORY_TYPE_APPLICATION].allocatedAmount + baMemoryLookupTable[SBR_MEMORY_TYPE_CHANNEL].allocatedAmount +
                                                baMemoryLookupTable[SBR_MEMORY_TYPE_EMOJI].allocatedAmount + baMemoryLookupTable[SBR_MEMORY_TYPE_GUILD].allocatedAmount + baMemoryLookupTable[SBR_MEMORY_TYPE_GUILD_MEMBER].allocatedAmount +
                                                baMemoryLookupTable[SBR_MEMORY_TYPE_MESSAGE].allocatedAmount + baMemoryLookupTable[SBR_MEMORY_TYPE_USER].allocatedAmount,
                                                baMemoryLookupTable[SBR_MEMORY_TYPE_SNOWFLAKE].allocatedBytes + baMemoryLookupTable[SBR_MEMORY_TYPE_APPLICATION].allocatedBytes + baMemoryLookupTable[SBR_MEMORY_TYPE_CHANNEL].allocatedBytes +
                                                baMemoryLookupTable[SBR_MEMORY_TYPE_EMOJI].allocatedBytes + baMemoryLookupTable[SBR_MEMORY_TYPE_GUILD].allocatedBytes + baMemoryLookupTable[SBR_MEMORY_TYPE_GUILD_MEMBER].allocatedBytes +
                                                baMemoryLookupTable[SBR_MEMORY_TYPE_MESSAGE].allocatedBytes + baMemoryLookupTable[SBR_MEMORY_TYPE_USER].allocatedBytes,
                                        BA_MEMORY_GET_MEMORY_INFORMATION(SBR_MEMORY_TYPE_SNOWFLAKE),
                                        BA_MEMORY_GET_MEMORY_INFORMATION(SBR_MEMORY_TYPE_APPLICATION),
                                        BA_MEMORY_GET_MEMORY_INFORMATION(SBR_MEMORY_TYPE_CHANNEL),
                                        BA_MEMORY_GET_MEMORY_INFORMATION(SBR_MEMORY_TYPE_EMOJI),
                                        BA_MEMORY_GET_MEMORY_INFORMATION(SBR_MEMORY_TYPE_GUILD),
                                        BA_MEMORY_GET_MEMORY_INFORMATION(SBR_MEMORY_TYPE_GUILD_MEMBER),
                                        BA_MEMORY_GET_MEMORY_INFORMATION(SBR_MEMORY_TYPE_MESSAGE),
                                        BA_MEMORY_GET_MEMORY_INFORMATION(SBR_MEMORY_TYPE_USER));
    return finalString;
}
