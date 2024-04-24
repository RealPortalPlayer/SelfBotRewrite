// Copyright (c) 2024, PortalPlayer <email@portalplayer.xyz>
// Licensed under MIT <https://opensource.org/licenses/MIT>

#include <stdlib.h>
#include <BaconAPI/Debugging/Assert.h>

#include "Discord/Snowflake.h"

SBR_Snowflake* SBR_Snowflake_ConvertFromNumber(uint64_t number) {
    SBR_Snowflake* snowflake = malloc(sizeof(SBR_Snowflake));

    BA_ASSERT(snowflake != NULL, "Failed to allocate memory for snowflake\n");

    // TODO: Discord sure loves their magic numbers
    snowflake->timestamp = (number >> 22) + SBR_SNOWFLAKE_EPOCH;
    snowflake->workerId = (number & 0x3E0000) >> 17;
    snowflake->processId = (number & 0x1F000) >> 12;
    snowflake->increment = number & 0xFFF;
    snowflake->original = number;
    return snowflake;
}
