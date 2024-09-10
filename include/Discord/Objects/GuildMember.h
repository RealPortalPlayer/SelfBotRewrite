// Purpose: Discord guild member
// Created on: 9/8/24 @ 7:43 PM

// Copyright (c) 2024, PortalPlayer <email@portalplayer.xyz>
// Licensed under MIT <https://opensource.org/licenses/MIT>

#pragma once

#include <BaconAPI/Storage/DynamicArray.h>
#include <json_object.h>
#include <time.h>

#include "User.h"
#include "../Permissions.h"

typedef enum {
    SBR_DISCORDGUILDMEMBER_CUSTOM_FLAG_DEAF = 1 << 0,
    SBR_DISCORDGUILDMEMBER_CUSTOM_FLAG_MUTE = 1 << 1,
    SBR_DISCORDGUILDMEMBER_CUSTOM_FLAG_PENDING = 1 << 2
} SBR_DiscordGuildMember_CustomFlags;

typedef enum {
    /**
     * User has been here before
     */
    SBR_DISCORDGUILDMEMBER_OFFICIAL_FLAG_DID_REJOIN = 1 << 0,
    SBR_DISCORDGUILDMEMBER_OFFICIAL_FLAG_COMPLETED_ONBOARDING = 1 << 1,
    SBR_DISCORDGUILDMEMBER_OFFICIAL_FLAG_BYPASSES_VERIFICATION = 1 << 2,
    SBR_DISCORDGUILDMEMBER_OFFICIAL_FLAG_STARTED_ONBOARDING = 1 << 3,
    SBR_DISCORDGUILDMEMBER_OFFICIAL_FLAG_IS_GUEST = 1 << 4,
    SBR_DISCORDGUILDMEMBER_OFFICIAL_FLAG_STARTED_HOME_ACTIONS = 1 << 5,
    SBR_DISCORDGUILDMEMBER_OFFICIAL_FLAG_COMPLETED_HOME_ACTIONS = 1 << 6,

    /**
     * Username, display name, or nickname was blocked automatically
     */
    SBR_DISCORDGUILDMEMBER_OFFICIAL_FLAG_AUTOMATIC_MODERATION_QUARANTINED_USERNAME = 1 << 7,
    SBR_DISCORDGUILDMEMBER_OFFICIAL_FLAG_DIRECT_MESSAGE_SETTINGS_UPSELL_ACKNOWLEDGED = 1 << 9
} SBR_DiscordGuildMember_OfficialFlags;

typedef struct {
    SBR_DiscordUser* user;
    const char* nick;
    const char* avatarHash;
    BA_DynamicArray* roles;
    struct tm* joinedAt;
    struct tm* premiumSince;
    SBR_DiscordGuildMember_CustomFlags customFlags;
    SBR_DiscordGuildMember_OfficialFlags officialFlags;
    SBR_DiscordPermissions permissions;
    struct tm* communicationDisabledUntil;
    // TODO: avatar_decoration_data
} SBR_DiscordGuildMember;

SBR_DiscordGuildMember* SBR_DiscordGuildMember_Create(json_object* unparsedJsonData);

void SBR_DiscordGuildMember_Deallocate(SBR_DiscordGuildMember* guildMember);
