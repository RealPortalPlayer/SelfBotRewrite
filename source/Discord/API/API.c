// Copyright (c) 2024, PortalPlayer <email@portalplayer.xyz>
// Licensed under MIT <https://opensource.org/licenses/MIT>

#include <BaconAPI/Logger.h>
#include <BaconAPI/Debugging/Assert.h>
#include <BaconAPI/String.h>
#include <json_tokener.h>

#include "Discord/API/API.h"
#include "Discord/API/Events.h"

BA_Boolean SBR_DiscordAPI_Send(SBR_DiscordAPIEvent_Codes code, json_object* data, json_object** output, const SBR_DiscordAPIEvents_Variables* variables) {
    BA_LOGGER_TRACE("Sending API: %i\n", code);

    if (!SBR_DiscordAPIEvent_IsCodeValid(code)) {
        BA_LOGGER_ERROR("Invalid code: %i\n", code);
        return BA_BOOLEAN_FALSE;
    }
    
    *output = SBR_DiscordAPIEvents_Get(code)->action(data, variables);
    // TODO: Parse error
    return BA_BOOLEAN_TRUE;
}
