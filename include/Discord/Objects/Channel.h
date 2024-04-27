// Purpose: Discord channels
// Created on: 4/27/24 @ 1:58 PM

// Copyright (c) 2024, PortalPlayer <email@portalplayer.xyz>
// Licensed under MIT <https://opensource.org/licenses/MIT>

#pragma once

#include "Snowflake.h"

// TODO: Channel object

json_object* SBR_DiscordChannel_Send(const SBR_Snowflake* id, const char* content);
