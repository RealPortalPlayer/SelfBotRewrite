// Purpose: Registered API events
// Created on: 4/27/24 @ 2:53 PM

// Copyright (c) 2024, PortalPlayer <email@portalplayer.xyz>
// Licensed under MIT <https://opensource.org/licenses/MIT>

#pragma once

#include <json_object.h>

#include "Event.h"
#include "../Objects/Snowflake.h"
#include "../Objects/Message.h"
#include "Discord/EmbedCreator.h"

typedef union  {
    const SBR_Snowflake* snowflake;
} SBR_DiscordAPIEvents_Variables;

typedef json_object* (*SBR_DiscordAPIEvents_Function)(json_object* data, const SBR_DiscordAPIEvents_Variables* variables);

typedef struct {
    SBR_DiscordAPIEvent_Codes code;
    SBR_DiscordAPIEvents_Function action;
} SBR_DiscordAPIEvents_Information;

const SBR_DiscordAPIEvents_Information* SBR_DiscordAPIEvents_Get(SBR_DiscordAPIEvent_Codes code);

/**
 * Not the same as the channel one.
 */
SBR_DiscordMessage* SBR_DiscordAPIEvents_SendMessage(const SBR_Snowflake* id, const char* content, SBR_EmbedCreator_Embed* embed);
SBR_DiscordChannel* SBR_DiscordAPIEvents_GetChannel(const SBR_Snowflake* id);
SBR_DiscordGuild* SBR_DiscordAPIEvents_GetGuild(const SBR_Snowflake* id);
