// Purpose: Registered API events
// Created on: 4/27/24 @ 2:53 PM

// Copyright (c) 2024, PortalPlayer <email@portalplayer.xyz>
// Licensed under MIT <https://opensource.org/licenses/MIT>

#pragma once

#include <json_object.h>

#include "Event.h"

typedef char* (*SBR_DiscordAPIEvents_Function)(const json_object* data);

SBR_DiscordAPIEvents_Function SBR_DiscordAPIEvents_GetFunction(SBR_DiscordAPIEvent_Codes code);
char* SBR_DiscordAPIEvents_GetMessagesURL(const json_object* data);
