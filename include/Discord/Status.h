// Purpose: Discord status information
// Created on: 4/26/24 @ 6:26 PM

// Copyright (c) 2024, PortalPlayer <email@portalplayer.xyz>
// Licensed under MIT <https://opensource.org/licenses/MIT>

#pragma once

typedef enum  {
    SBR_DISCORDSTATUS_ONLINE,
    SBR_DISCORDSTATUS_DO_NOT_DISTURB,
    SBR_DISCORDSTATUS_IDLE,
    SBR_DISCORDSTATUS_INVISIBLE
} SBR_DiscordStatus;

const char* SBR_DiscordStatus_ToString(SBR_DiscordStatus status);
SBR_DiscordStatus SBR_DiscordStatus_FromString(const char* status);
