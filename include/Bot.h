// Purpose: Main bot
// Created on: 4/26/24 @ 7:52 PM

// Copyright (c) 2024, PortalPlayer <email@portalplayer.xyz>
// Licensed under MIT <https://opensource.org/licenses/MIT>

#pragma once

#include "Discord/User.h"

const SBR_DiscordUser* SBR_Bot_Get(void);

void SBR_Bot_Set(SBR_DiscordUser* user);
