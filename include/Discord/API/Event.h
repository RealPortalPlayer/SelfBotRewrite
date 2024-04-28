// Purpose: Discord API "events"
// Created on: 4/27/24 @ 2:42 PM

// Copyright (c) 2024, PortalPlayer <email@portalplayer.xyz>
// Licensed under MIT <https://opensource.org/licenses/MIT>

#pragma once

#include <BaconAPI/Internal/Boolean.h>

typedef enum {
    SBR_DISCORDAPIEVENT_CODE_CREATE_MESSAGE,
    SBR_DISCORDAPIEVENT_CODE_GET_CHANNEL,

    /**
     * Not a real code
     */
    SBR_DISCORDAPIEVENT_CODE_SIZE
} SBR_DiscordAPIEvent_Codes;

BA_Boolean SBR_DiscordAPIEvent_IsCodeValid(SBR_DiscordAPIEvent_Codes code);
