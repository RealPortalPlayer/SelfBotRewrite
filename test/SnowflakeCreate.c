// Copyright (c) 2024, PortalPlayer <email@portalplayer.xyz>
// Licensed under MIT <https://opensource.org/licenses/MIT>

#include <BaconAPI/ArgumentHandler.h>
#include <stdint.h>
#include <BaconAPI/Number.h>
#include <BaconAPI/Logger.h>
#include <BaconAPI/Debugging/Assert.h>
#include <Discord/Objects/Snowflake.h>

#define GET_NUMBER(variable, id, function) \
if (argc >= id + 1)                        \
    variable = function(argv[id], NULL, NULL, NULL, variable)

int main(int argc, char** argv) {
    BA_ArgumentHandler_Initialize(argc, argv);

    uint64_t timestamp = 1504361180003;
    uint8_t workerId = 1;
    uint8_t processId = 0;
    uint32_t increment = 1;

    GET_NUMBER(timestamp, 1, BA_Number_StringToUnsignedLong);
    GET_NUMBER(workerId, 2, BA_Number_StringToUnsigned);
    GET_NUMBER(processId, 3, BA_Number_StringToUnsigned);
    GET_NUMBER(increment, 4, BA_Number_StringToUnsigned);

    if (timestamp < SBR_SNOWFLAKE_EPOCH)
        BA_LOGGER_WARN("Your snowflake is invalid: timestamp is less than epoch (%lu, by %lu)\n", SBR_SNOWFLAKE_EPOCH, SBR_SNOWFLAKE_EPOCH - timestamp);
    
    uint64_t snowflake = SBR_Snowflake_Create(timestamp, workerId, processId, increment);
    
    BA_LOGGER_INFO("Snowflake: %lu\n", snowflake);

    if (argc >= 2)
        return 0;

    BA_ASSERT(snowflake == 353541155729833985, "Failed to create snowflake\n");
}
