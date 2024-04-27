// Copyright (c) 2024, PortalPlayer <email@portalplayer.xyz>
// Licensed under MIT <https://opensource.org/licenses/MIT>

#include <BaconAPI/Logger.h>
#include <BaconAPI/Debugging/Assert.h>
#include <BaconAPI/String.h>
#include <json_tokener.h>

#include "Discord/API/API.h"
#include "Discord/API/Events.h"
#include "cURL.h"

BA_Boolean SBR_DiscordAPI_Send(SBR_DiscordAPIEvent_Codes code, json_object* data, json_object** output) {
    BA_LOGGER_TRACE("Sending API: %i\n", code);
    BA_ASSERT(SBR_DiscordAPIEvent_IsCodeValid(code), "Invalid code: %i\n", code);

    char* url = SBR_DiscordAPIEvents_GetFunction(code)(data);
    json_object* dataData = json_object_object_get(data, "data");
    char* buffer = BA_String_CreateEmpty();

    BA_ASSERT(buffer != NULL, "Failed to create a buffer for API response\n");
    BA_ASSERT(dataData != NULL, "Malformed packet: missing JSON fields\n");
    SBR_cURL_HTTPSend(url, json_object_to_json_string(dataData), BA_BOOLEAN_TRUE, &buffer); // TODO

    // TODO: Parse error
    *output = json_tokener_parse(buffer);

    free(buffer);
    free(url);
    return BA_BOOLEAN_TRUE;
}
