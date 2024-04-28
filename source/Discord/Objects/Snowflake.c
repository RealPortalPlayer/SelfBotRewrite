// Copyright (c) 2024, PortalPlayer <email@portalplayer.xyz>
// Licensed under MIT <https://opensource.org/licenses/MIT>

#include <stdlib.h>
#include <BaconAPI/Debugging/Assert.h>

#include "Discord/Objects/Snowflake.h"

SBR_Snowflake* SBR_Snowflake_ConvertFromNumber(uint64_t number) {
    SBR_Snowflake* snowflake = malloc(sizeof(SBR_Snowflake));

    BA_ASSERT(snowflake != NULL, "Failed to allocate memory for snowflake\n");

    // TODO: Discord sure loves their magic numbers
    snowflake->timestamp = (number >> 22) + SBR_SNOWFLAKE_EPOCH;
    snowflake->workerId = (number & 0x3E0000) >> 17;
    snowflake->processId = (number & 0x1F000) >> 12;
    snowflake->increment = number & 0xFFF;
    return snowflake;
}

uint64_t SBR_Snowflake_ConvertToNumber(const SBR_Snowflake* snowflake) {
    return snowflake->timestamp - SBR_SNOWFLAKE_EPOCH << 22 |
           snowflake->workerId << 17 |
           snowflake->processId << 12 |
           snowflake->increment;
}
