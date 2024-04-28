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

    if (*output == NULL)
        return BA_BOOLEAN_FALSE;

    {
        json_object* errorCode = json_object_object_get(*output, "code");
        json_object* errorMessage = json_object_object_get(*output, "message");
        
        if (json_object_get_type(errorCode) != json_type_null) {
            BA_LOGGER_ERROR("Discord API error (%i): %s\n", json_object_get_int(errorCode), json_object_get_string(errorMessage));
            return BA_BOOLEAN_FALSE;
        }

        if (json_object_get_type(errorCode) != json_type_null) {
            BA_LOGGER_ERROR("Discord API error (HTTP): %s\n", json_object_get_string(errorMessage));
            return BA_BOOLEAN_FALSE;
        }
    }
    
    return BA_BOOLEAN_TRUE;
}
