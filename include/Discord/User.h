// Purpose: Discord user
// Created on: 4/26/24 @ 6:42 PM

// Copyright (c) 2024, PortalPlayer <email@portalplayer.xyz>
// Licensed under MIT <https://opensource.org/licenses/MIT>

#pragma once

#include <json_object.h>

#include "./Snowflake.h"

typedef enum {
    SBR_DISCORDUSER_CUSTOM_FLAG_NULL = 0,

    /**
     * HELLO FELLOW BOT! HOW ARE YOU?
     */
    SBR_DISCORDUSER_CUSTOM_FLAG_BOT = 1 << 0,

    /**
     * User is part of the urgent message system
     */
    SBR_DISCORDUSER_CUSTOM_FLAG_SYSTEM = 1 << 1,
    SBR_DISCORDUSER_CUSTOM_FLAG_MULTI_FACTOR_AUTHENTICATION_ENABLED = 1 << 2,
    SBR_DISCORDUSER_CUSTOM_FLAG_EMAIL_VERIFIED = 1 << 3,
} SBR_DiscordUser_CustomFlags;

typedef enum {
    SBR_DISCORDUSER_LOCALE_INDONESIAN,
    SBR_DISCORDUSER_LOCALE_DANISH,
    SBR_DISCORDUSER_LOCALE_GERMAN,
    SBR_DISCORDUSER_LOCALE_BRITISH_ENGLISH,
    SBR_DISCORDUSER_LOCALE_AMERICAN_ENGLISH,
    SBR_DISCORDUSER_LOCALE_SPANISH,
    SBR_DISCORDUSER_LOCALE_FRENCH,
    SBR_DISCORDUSER_LOCALE_CROATIAN,
    SBR_DISCORDUSER_LOCALE_ITALIAN,
    SBR_DISCORDUSER_LOCALE_LITHUANIAN,
    SBR_DISCORDUSER_LOCALE_HUNGARIAN,
    SBR_DISCORDUSER_LOCALE_DUTCH,
    SBR_DISCORDUSER_LOCALE_NORWEIGAN,
    SBR_DISCORDUSER_LOCALE_POLISH,
    SBR_DISCORDUSER_LOCALE_PORTUGUESE,
    SBR_DISCORDUSER_LOCALE_ROMANIAN,
    SBR_DISCORDUSER_LOCALE_FINNISH,
    SBR_DISCORDUSER_LOCALE_SWEDISH,
    SBR_DISCORDUSER_LOCALE_VIETNAMESE,
    SBR_DISCORDUSER_LOCALE_TURKISH,
    SBR_DISCORDUSER_LOCALE_CZECH,
    SBR_DISCORDUSER_LOCALE_GREEK,
    SBR_DISCORDUSER_LOCALE_BULGARIAN,
    SBR_DISCORDUSER_LOCALE_RUSSIAN,
    SBR_DISCORDUSER_LOCALE_UKRAINIAN,
    SBR_DISCORDUSER_LOCALE_HINDI,
    SBR_DISCORDUSER_LOCALE_CHINESE,
    SBR_DISCORDUSER_LOCALE_JAPANENSE
} SBR_DiscordUser_Locales;

typedef enum {
    /**
     * Employee to Discord
     */
    SBR_DISCORDUSER_OFFICIAL_FLAG_STAFF = 1 << 0,

    /**
     * Is a partner to Discord
     */
    SBR_DISCORDUSER_OFFICIAL_FLAG_PARTNER = 1 << 1,

    /**
     * User attended a HypeSquad event when those were still a thing
     */
    SBR_DISCORDUSER_OFFICIAL_FLAG_HYPESQUAD_EVENTS = 1 << 2,
    SBR_DISCORDUSER_OFFICIAL_FLAG_BUG_HUNTER_LEVEL_1 = 1 << 3,
    SBR_DISCORDUSER_OFFICIAL_FLAG_HYPESQUAD_BRAVERY_HOUSE = 1 << 6,
    SBR_DISCORDUSER_OFFICIAL_FLAG_HYPESQUAD_BRILLIANCE_HOUSE = 1 << 7,
    SBR_DISCORDUSER_OFFICIAL_FLAG_HYPESQUAD_BALANCE_HOUSE = 1 << 8,

    /**
     * User owned Nitro before Oct. 10, 2018
     */
    SBR_DISCORDUSER_OFFICIAL_FLAG_EARY_NITRO_SUPPORTER = 1 << 9,

    /**
     * This is not a real user
     */
    SBR_DISCORDUSER_OFFICIAL_FLAG_TEAM = 1 << 10,
    SBR_DISCORDUSER_OFFICIAL_FLAG_BUG_HUNTER_LEVEL_2 = 1 << 14,
    SBR_DISCORDUSER_OFFICIAL_FLAG_VERIFIED_BOT = 1 << 16,

    /**
     * User submitted for their bot to be verified before Aug. 19th 2020, and got accepted
     */
    SBR_DISCORDUSER_OFFICIAL_FLAG_VERIFIED_DEVELOPER = 1 << 17,

    /**
     * User was part of the moderator ecosystem before Dec. 1st 2022
     */
    SBR_DISCORDUSER_OFFICIAL_FLAG_CERTIFIED_MODERATOR = 1 << 18,

    /**
     * Bot can't use Gateway (i.e. webhooks)
     */
    SBR_DISCORDUSER_OFFICIAL_FLAG_BOT_HTTP_INTERACTIONS = 1 << 19,
    SBR_DISCORDUSER_OFFICIAL_FLAG_ACTIVE_DEVELOPER = 1 << 22
} SBR_DiscordUser_OfficialFlags;

typedef enum {
    SBR_DISCORDUSER_NITRO_TYPE_NONE,

    /**
     * @deprecated Replaced with Nitro Basic. User is either grandfathered in, or used a trick to receive it
     */
    SBR_DISCORDUSER_NITRO_TYPE_NITRO_CLASSIC,
    SBR_DISCORDUSER_NITRO_TYPE_NITRO,
    SBR_DISCORDUSER_NITRO_TYPE_NITRO_BASIC
} SBR_DiscordUser_NitroTypes;

typedef struct {
    SBR_Snowflake* id;
    const char* username;

    /**
     * @note Some users have not migrated yet. Bots are still unknown
     * @deprecated
     */
    const char* discriminator;
    const char* globalName;
    const char* avatarHash;
    SBR_DiscordUser_CustomFlags customFlags;
    const char* bannerHash;
    int accentColor;
    SBR_DiscordUser_Locales locale;
    const char* email;
    SBR_DiscordUser_OfficialFlags officialFlags;
    SBR_DiscordUser_NitroTypes nitro;
    SBR_DiscordUser_OfficialFlags publicOfficialFlags;
    const char* avatarDecoration;
} SBR_DiscordUser;

SBR_DiscordUser* SBR_DiscordUser_Create(json_object* userData);
