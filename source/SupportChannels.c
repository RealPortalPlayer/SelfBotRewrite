// Copyright (c) 2024, PortalPlayer <email@portalplayer.xyz>
// Licensed under MIT <https://opensource.org/licenses/MIT>

#include <BaconAPI/Debugging/Assert.h>
#include <BaconAPI/Number.h>

#include "SupportChannels.h"
#include "Settings.h"
#include "Discord/API/Events.h"

#define SBR_SUPPORTCHANNELS_CREATE_FUNCTION(type, settingName, errorType) \
SBR_SUPPORTCHANNELS_CREATE_FUNCTION_HEADER(type) {                        \
    static SBR_Snowflake* snowflake = NULL;                               \
    if (snowflake == NULL) {                                              \
        char* id;                                                         \
        BA_Boolean isError;                                               \
        BA_ASSERT(SBR_Settings_Get(settingName "_CHANNEL", &id, BA_BOOLEAN_FALSE), "Cannot find " errorType " channel ID\n"); \
        uint64_t parsedNumber = BA_Number_StringToUnsignedLong(id, NULL, &isError, NULL, 0); \
        BA_ASSERT(!isError, "Failed to parse " errorType " channel ID\n"); \
        snowflake = SBR_Snowflake_ConvertFromNumber(parsedNumber);        \
    }                                                                     \
    return SBR_DiscordAPIEvents_SendMessage(snowflake, content, embed);   \
}

SBR_SUPPORTCHANNELS_CREATE_FUNCTION(Logs, "LOGS", "logs")
SBR_SUPPORTCHANNELS_CREATE_FUNCTION(Bugs, "BUGS", "bugs")
SBR_SUPPORTCHANNELS_CREATE_FUNCTION(Suggestions, "SUGGESTIONS", "suggestions")
