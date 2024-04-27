// Purpose: Discord API helper
// Created on: 4/27/24 @ 2:50 PM

// Copyright (c) 2024, PortalPlayer <email@portalplayer.xyz>
// Licensed under MIT <https://opensource.org/licenses/MIT>

#pragma once

#include <json_object.h>

#include "Event.h"
#include "Events.h"

/**
 * 
 * @param code 
 * @param data - {*: anything the API code needs, data: json to be sent to Discord}
 * @param output
 * @return False means there was an API error
 */
BA_Boolean SBR_DiscordAPI_Send(SBR_DiscordAPIEvent_Codes code, json_object* data, json_object** output, const SBR_DiscordAPIEvents_Variables* variables);
