// Purpose: Discord guild/server
// Created on: 4/27/24 @ 9:46 AM

// Copyright (c) 2024, PortalPlayer <email@portalplayer.xyz>
// Licensed under MIT <https://opensource.org/licenses/MIT>

#pragma once

#include <BaconAPI/Internal/Boolean.h>
#include <BaconAPI/Storage/DynamicArray.h>

#include "json_object.h"
#include "Snowflake.h"
#include "../Locale.h"
#include "User.h"

typedef enum {
    SBR_DISCORDGUILD_VERIFICATION_LEVEL_NULL,

    /**
     * Users requires a verified email
     */
    SBR_DISCORDGUILD_VERIFICATION_LEVEL_LOW,

    /**
     * Users must be registered on Discord for longer than 5 minutes
     */
    SBR_DISCORDGUILD_VERIFICATION_LEVEL_MEDIUM,

    /**
     * Users must be a member of the guild for longer than 10 minutes
     */
    SBR_DISCORDGUILD_VERIFICATION_LEVEL_HIGH,

    /**
     * Users must have a verified phone number
     */
    SBR_DISCORDGUILD_VERIFICATION_LEVEL_VERY_HIGH
} SBR_DiscordGuild_VerificationLevels;

typedef enum {
    SBR_DISCORDGUILD_BOOST_LEVEL_NULL,
    SBR_DISCORDGUILD_BOOST_LEVEL_TIER_1,
    SBR_DISCORDGUILD_BOOST_LEVEL_TIER_2,
    SBR_DISCORDGUILD_BOOST_LEVEL_TIER_3
} SBR_DiscordGuild_BoostLevels;

typedef enum {
    SBR_DISCORDGUILD_EXPLICIT_CONTENT_FILTER_LEVEL_DISABLED,
    SBR_DISCORDGUILD_EXPLICIT_CONTENT_FILTER_LEVEL_MEMBERS_WITHOUT_ROLES,
    SBR_DISCORDGUILD_EXPLICIT_CONTENT_FILTER_LEVEL_ALL_MEMBERS
} SBR_DiscordGuild_ExplicitContentFilterLevels;

typedef enum {
    SBR_DISCORDGUILD_CUSTOM_FLAG_NOTIFICATIONS_MENTIONS_ONLY = 1 << 0,
    SBR_DISCORDGUILD_CUSTOM_FLAG_REQUIRES_MULTI_FACTOR_AUTHENTICATION = 1 << 1,
    SBR_DISCORDGUILD_CUSTOM_FLAG_WIDGETS_ENABLED = 1 << 2,
    SBR_DISCORDGUILD_CUSTOM_FLAG_PREMIUM_PROGRESS_BAR_ENABLED = 1 << 3
} SBR_DiscordGuild_CustomFlags;

typedef enum {
    SBR_DISCORDGUILD_SYSTEM_CHANNEL_FLAG_SUPPRESS_JOIN_NOTIFICATIONS = 1 << 0,
    SBR_DISCORDGUILD_SYSTEM_CHANNEL_FLAG_SUPPRESS_PREMIUM_SUBSCRIPTIONS = 1 << 1,
    SBR_DISCORDGUILD_SYSTEM_CHANNEL_FLAG_SUPPRESS_GUILD_REMINDER_NOTIFICATIONS = 1 << 2,
    SBR_DISCORDGUILD_SYSTEM_CHANNEL_FLAG_SUPPRESS_JOIN_NOTIFICATION_REPLIES = 1 << 3,
    SBR_DISCORDGUILD_SYSTEM_CHANNEL_FLAG_SUPPRESS_ROLE_SUBSCRIPTION_PURCHASE_NOTIFICATIONS = 1 << 4,
    SBR_DISCORDGUILD_SYSTEM_CHANNEL_FLAG_SUPPRESS_ROLE_SUBSCRIPTION_PURCHASE_NOTIFICATION_REPLIES=  1 << 5
} SBR_DiscordGuild_SystemChannelFlags;

typedef enum {
    /**
     * Not marked. Not the same as SBR_DISCORDGUILD_NOT_SAFE_FOR_WORK_LEVEL_SAFE
     */
    SBR_DISCORDGUILD_NOT_SAFE_FOR_WORK_LEVEL_NULL,

    /**
     * Guild has pornographic content
     */
    SBR_DISCORDGUILD_NOT_SAFE_FOR_WORK_LEVEL_EXPLICIT,
    SBR_DISCORDGUILD_NOT_SAFE_FOR_WORK_LEVEL_SAFE,

    /**
     * Guild might have explicit language
     */
    SBR_DISCORDGUILD_NOT_SAFE_FOR_WORK_LEVEL_AGE_RESTRICTED
} SBR_DiscordGuild_NotSafeForWorkLevels;

typedef enum {
    SBR_DISCORDGUILD_FEATURE_NULL,
    SBR_DISCORDGUILD_FEATURE_ALLOWED_ANIMATED_BANNER = 1 << 0,
    SBR_DISCORDGUILD_FEATURE_ALLOWED_ANIMATED_ICON = 1 << 1,

    /**
     * @deprecated Might already have been removed
     */
    SBR_DISCORDGUILD_FEATURE_DEPRECATED_COMMAND_SYSTEM = 1 << 2,
    SBR_DISCORDGUILD_FEATURE_HAS_AUTO_MODERATION_RULES = 1 << 3,
    SBR_DISCORDGUILD_FEATURE_ALLOWED_BANNER = 1 << 4,
    SBR_DISCORDGUILD_FEATURE_COMMUNITY = 1 << 5,
    SBR_DISCORDGUILD_FEATURE_ENABLED_MONETIZATION = 1 << 6,
    SBR_DISCORDGUILD_FEATURE_ENABLED_ROLE_SUBSCRIPTION_PROMOTIONAL_PAGE = 1 << 7,
    SBR_DISCORDGUILD_FEATURE_SUPPORT_GUILD = 1 << 8,
    SBR_DISCORDGUILD_FEATURE_DISCOVERABLE = 1 << 9,
    SBR_DISCORDGUILD_FEATURE_FEATURABLE = 1 << 10,
    SBR_DISCORDGUILD_FEATURE_INVITES_DISABLED = 1 << 11,
    SBR_DISCORDGUILD_FEATURE_ALLOWED_INVITE_SPLASH = 1 << 12,
    SBR_DISCORDGUILD_FEATURE_ENABLED_MEMBERSHIP_SCREENING = 1 << 13,
    SBR_DISCORDGUILD_FEATURE_MORE_STICKERS = 1 << 14,
    SBR_DISCORDGUILD_FEATURE_ALLOWED_ANNOUNCEMENT_CHANNELS = 1 << 15,
    SBR_DISCORDGUILD_FEATURE_PARTNERED = 1 << 16,
    SBR_DISCORDGUILD_FEATURE_ENABLED_PREVIEWING = 1 << 17,
    SBR_DISCORDGUILD_FEATURE_DISABLED_RAID_ALERTS = 1 << 18,
    SBR_DISCORDGUILD_FEATURE_ALLOWED_ROLE_ICONS = 1 << 19,
    SBR_DISCORDGUILD_FEATURE_HAS_ROLE_SUBSCRIPTIONS_AVAILABLE = 1 << 20,
    SBR_DISCORDGUILD_FEATURE_ENABLED_TICKETED_EVENTS = 1 << 21,
    SBR_DISCORDGUILD_FEATURE_ALLOWED_VANITY_URL = 1 << 22,
    SBR_DISCORDGUILD_FEATURE_VERIFIED = 1 << 23,

    /**
     * Guild has access to 384kbps bitrate inside voice channels
     */
    SBR_DISCORDGUILD_FEATURE_VIP_REGIONS = 1 << 24,
    SBR_DISCORDGUILD_FEATURE_ENABLED_WELCOME_SCREEN = 1 << 25
} SBR_DiscordGuild_Features;

typedef struct {
    /**
     * If true, then only this and ID would be defined. 
     */
    BA_Boolean unavailable;
    SBR_Snowflake* id;
    const char* name;
    const char* iconHash;
    const char* templateIconHash;
    const char* splashHash;
    const char* discoverySplashHash;
    SBR_DiscordUser* owner;
    SBR_Snowflake* ownerId;
    SBR_Snowflake* afkChannelId;
    int afkTimeoutSeconds;
    SBR_DiscordGuild_CustomFlags customFlags;
    SBR_Snowflake* widgetChannelId;
    SBR_DiscordGuild_VerificationLevels verificationLevel;
    SBR_DiscordGuild_ExplicitContentFilterLevels filterLevel;
    BA_DynamicArray* roles;
    BA_DynamicArray* emojis;
    SBR_DiscordGuild_Features features;

    /**
     * If the owner is a bot
     */
    SBR_Snowflake* applicationId;
    SBR_Snowflake* systemChannelId;
    SBR_DiscordGuild_SystemChannelFlags systemChannelFlags;
    SBR_Snowflake* rulesChannelId;
    int maxPresences;
    int maxMembers;
    const char* vanityUrlCode;
    const char* description;
    const char* bannerHash;
    SBR_DiscordGuild_BoostLevels boostLevel;
    int boostCount;
    SBR_DiscordLocales preferredLocale;
    SBR_Snowflake* publicUpdatesChannelId;
    int maxVideoChannelUsers;
    int maxStageVideoChannelUsers;
    int approximateMemberCount;
    int approximatePresenceCount;
    // TODO: welcomeScreen
    SBR_DiscordGuild_NotSafeForWorkLevels notSafeForWorkLevel;
    BA_DynamicArray* stickers;
    SBR_Snowflake* safetyAlertsChannelId;
    struct SBR_DiscordChannel* afkChannel;
    struct SBR_DiscordChannel* widgetChannel;
    struct SBR_DiscordChannel* systemChannel;
    struct SBR_DiscordChannel* rulesChannel;
} SBR_DiscordGuild;

SBR_DiscordGuild* SBR_DiscordGuild_Create(json_object* unparsedJsonData);

SBR_DiscordGuild* SBR_DiscordGuild_Get(const SBR_Snowflake* id);
