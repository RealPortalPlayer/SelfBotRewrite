// Copyright (c) 2024, PortalPlayer <email@portalplayer.xyz>
// Licensed under MIT <https://opensource.org/licenses/MIT>

#include <stdlib.h>
#include <BaconAPI/Debugging/Assert.h>

#include "Discord/Objects/Snowflake.h"
#include "Memory.h"

SBR_Snowflake* SBR_Snowflake_ConvertFromNumber(uint64_t number) {
    SBR_Snowflake* snowflake = BA_Memory_Allocate(sizeof(SBR_Snowflake), SBR_MEMORY_TYPE_SNOWFLAKE);

    BA_ASSERT(snowflake != NULL, "Failed to allocate memory for snowflake\n");

    // TODO: Discord sure loves their magic numbers
    snowflake->timestamp = (number >> 22) + SBR_SNOWFLAKE_EPOCH;
    snowflake->workerId = (number & 0x3E0000) >> 17;
    snowflake->processId = (number & 0x1F000) >> 12;
    snowflake->increment = number & 0xFFF;
    return snowflake;
}

uint64_t SBR_Snowflake_ConvertToNumber(const SBR_Snowflake* snowflake) {
    return SBR_Snowflake_Create(snowflake->timestamp, snowflake->workerId, snowflake->processId, snowflake->increment);
}

uint64_t SBR_Snowflake_Create(uint64_t timestamp, uint8_t workerId, uint8_t processId, uint32_t increment) {
    return timestamp - SBR_SNOWFLAKE_EPOCH << 22 |
           workerId << 17 |
           processId << 12 |
           increment;
}

void SBR_Snowflake_Deallocate(SBR_Snowflake* snowflake) {
    BA_Memory_Deallocate(snowflake, sizeof(SBR_Snowflake), SBR_MEMORY_TYPE_SNOWFLAKE);
}
