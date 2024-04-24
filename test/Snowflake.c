// Copyright (c) 2024, PortalPlayer <email@portalplayer.xyz>
// Licensed under MIT <https://opensource.org/licenses/MIT>

#include <BaconAPI/ArgumentHandler.h>
#include <BaconAPI/Logger.h>
#include <BaconAPI/Number.h>
#include <BaconAPI/Debugging/Assert.h>
#include <Discord/Snowflake.h>

#define ASSERT(variable, equals) BA_ASSERT(snowflake->variable == equals, "Invalid " #variable "\n")

int main(int argc, char** argv) {
    BA_ArgumentHandler_Initialize(argc, argv);

    uint64_t snowflakeId = 353541155729833985;
    BA_Boolean doAsserts = argc <= 1;

    if (!doAsserts)
        snowflakeId = BA_Number_StringToUnsignedLong(argv[1], NULL, NULL, NULL, snowflakeId);

    SBR_Snowflake* snowflake = SBR_Snowflake_ConvertFromNumber(snowflakeId);

    BA_LOGGER_INFO("Snowflake:\n"
                   "Timestamp: %li\n"
                   "Worker ID: %i\n"
                   "Process ID: %i\n"
                   "Increment: %i\n"
                   "Original: %li\n", snowflake->timestamp, snowflake->workerId, snowflake->processId, snowflake->increment, snowflake->original);

    if (!doAsserts)
        return 0;

    ASSERT(timestamp, 1504361180003);
    ASSERT(workerId, 1);
    ASSERT(processId, 0);
    ASSERT(increment, 1);
    ASSERT(original, 353541155729833985);
}