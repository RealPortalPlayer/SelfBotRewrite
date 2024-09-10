// Copyright (c) 2024, PortalPlayer <email@portalplayer.xyz>
// Licensed under MIT <https://opensource.org/licenses/MIT>

#include <BaconAPI/Debugging/Assert.h>
#include <BaconAPI/Number.h>

#include "SupportChannels.h"
#include "Settings.h"
#include "Discord/API/Events.h"

static SBR_Snowflake* sbrSupportChannelsLogs = NULL;
static SBR_Snowflake* sbrSupportChannelsBugs = NULL;
static SBR_Snowflake* sbrSupportChannelsSuggestions = NULL;

#define SBR_SUPPORTCHANNELS_CREATE_FUNCTION(type, settingName, errorType) \
SBR_SUPPORTCHANNELS_CREATE_FUNCTION_HEADER(type) {                        \
    if (sbrSupportChannels ## type == NULL) {                             \
        char* id;                                                         \
        BA_Boolean isError;                                               \
        BA_ASSERT(SBR_Settings_Get(settingName "_CHANNEL", &id, BA_BOOLEAN_FALSE), "Cannot find " errorType " channel ID\n"); \
        uint64_t parsedNumber = BA_Number_StringToUnsignedLong(id, NULL, &isError, NULL, 0); \
        BA_ASSERT(!isError, "Failed to parse " errorType " channel ID\n"); \
        sbrSupportChannels ## type = SBR_Snowflake_ConvertFromNumber(parsedNumber); \
    }                                                                     \
    return SBR_DiscordAPIEvents_SendMessage(sbrSupportChannels ## type, content, embed); \
}

SBR_SUPPORTCHANNELS_CREATE_FUNCTION(Logs, "LOGS", "logs")
SBR_SUPPORTCHANNELS_CREATE_FUNCTION(Bugs, "BUGS", "bugs")
SBR_SUPPORTCHANNELS_CREATE_FUNCTION(Suggestions, "SUGGESTIONS", "suggestions")

void SBR_SupportChannels_Deallocate(void) {
    SBR_Snowflake_Deallocate(sbrSupportChannelsLogs);
    SBR_Snowflake_Deallocate(sbrSupportChannelsBugs);
    SBR_Snowflake_Deallocate(sbrSupportChannelsSuggestions);
    
    sbrSupportChannelsLogs = NULL;
    sbrSupportChannelsBugs = NULL;
    sbrSupportChannelsSuggestions = NULL;
}
