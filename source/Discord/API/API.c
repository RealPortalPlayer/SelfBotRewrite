// Copyright (c) 2024, PortalPlayer <email@portalplayer.xyz>
// Licensed under MIT <https://opensource.org/licenses/MIT>

#include <BaconAPI/Logger.h>
#include <BaconAPI/String.h>
#include <json_tokener.h>
#include <BaconAPI/Thread.h>

#include "Discord/API/API.h"
#include "Discord/API/Events.h"
#include "Debugging/Assert.h"

BA_Boolean SBR_DiscordAPI_Send(SBR_DiscordAPIEvent_Codes code, json_object* data, json_object** output, const SBR_DiscordAPIEvents_Variables* variables) {
    static BA_Thread_Lock threadLock;
    static BA_Boolean initialized = BA_BOOLEAN_FALSE;

    if (!initialized) {
        SBR_ASSERT(BA_Thread_CreateLock(&threadLock), "Failed to create API message lock\n");

        initialized = BA_BOOLEAN_TRUE;
    }

    BA_Thread_UseLock(&threadLock);
    BA_LOGGER_TRACE("Sending API: %i\n", code);

    if (!SBR_DiscordAPIEvent_IsCodeValid(code)) {
        BA_LOGGER_ERROR("Invalid code: %i\n", code);
        BA_Thread_Unlock(&threadLock);
        return BA_BOOLEAN_FALSE;
    }
    
    *output = SBR_DiscordAPIEvents_Get(code)->action(data, variables);

    if (*output == NULL) {
        BA_Thread_Unlock(&threadLock);
        return BA_BOOLEAN_FALSE;
    }

    {
        json_object* errorCode = json_object_object_get(*output, "code");
        json_object* errorMessage = json_object_object_get(*output, "message");
        
        if (json_object_get_type(errorCode) != json_type_null) {
            BA_LOGGER_ERROR("Discord API error (%i): %s\n", json_object_get_int(errorCode), json_object_get_string(errorMessage));
            BA_Thread_Unlock(&threadLock);
            return BA_BOOLEAN_FALSE;
        }

        if (json_object_get_type(errorCode) != json_type_null) {
            BA_LOGGER_ERROR("Discord API error (HTTP): %s\n", json_object_get_string(errorMessage));
            BA_Thread_Unlock(&threadLock);
            return BA_BOOLEAN_FALSE;
        }
    }

    BA_Thread_Unlock(&threadLock);
    return BA_BOOLEAN_TRUE;
}
