// Purpose: Discord emoji
// Created on: 9/8/24 @ 6:10 PM

// Copyright (c) 2024, PortalPlayer <email@portalplayer.xyz>
// Licensed under MIT <https://opensource.org/licenses/MIT>

#pragma once

#include <BaconAPI/Storage/DynamicArray.h>

#include "Snowflake.h"
#include "User.h"

typedef enum {
    SBR_DISCORDEMOJI_CUSTOM_FLAG_REQUIRE_COLONS = 1 << 0,
    SBR_DISCORDEMOJI_CUSTOM_FLAG_MANAGED = 1 << 1,
    SBR_DISCORDEMOJI_CUSTOM_FLAG_ANIMATED = 1 << 2,
    SBR_DISCORDEMOJI_CUSTOM_FLAG_AVAILABLE = 1 << 3
} SBR_DiscordEmoji_CustomFlags;

typedef struct {
    SBR_Snowflake* id;
    const char* name;
    BA_DynamicArray* roles;
    SBR_DiscordUser* user;
    SBR_DiscordEmoji_CustomFlags customFlags;
} SBR_DiscordEmoji;

SBR_DiscordEmoji* SBR_DiscordEmoji_Create(json_object* unparsedJsonData);

void SBR_DiscordEmoji_Deallocate(SBR_DiscordEmoji* emoji);
