// Purpose: Discord channels
// Created on: 4/27/24 @ 1:58 PM

// Copyright (c) 2024, PortalPlayer <email@portalplayer.xyz>
// Licensed under MIT <https://opensource.org/licenses/MIT>

#pragma once

#include <json_object.h>
#include <time.h>

#include "Snowflake.h"
#include "../EmbedCreator.h"
#include "Guild.h"
#include "../Permissions.h"

typedef enum {
    SBR_DISCORDCHANNEL_TYPE_GUILD_TEXT,
    SBR_DISCORDCHANNEL_TYPE_DIRECT_MESSAGE,
    SBR_DISCORDCHANNEL_TYPE_GUILD_VOICE,
    SBR_DISCORDCHANNEL_TYPE_GROUP_DIRECT_MESSAGE,
    SBR_DISCORDCHANNEL_TYPE_GUILD_CATEGORY,
    SBR_DISCORDCHANNEL_TYPE_GUILD_ANNOUNCEMENT,
    SBR_DISCORDCHANNEL_TYPE_ANNOUNCEMENT_THREAD = 10,
    SBR_DISCORDCHANNEL_TYPE_PUBLIC_THREAD,
    SBR_DISCORDCHANNEL_TYPE_PRIVATE_THREAD,
    SBR_DISCORDCHANNEL_TYPE_GUILD_STAGE_VOICE,
    SBR_DISCORDCHANNEL_TYPE_GUILD_DIRECTORY,
    SBR_DISCORDCHANNEL_TYPE_GUILD_FORUM,
    SBR_DISCORDCHANNEL_TYPE_GUILD_MEDIA
} SBR_DiscordChannel_Types;

typedef enum {
    SBR_DISCORDCHANNEL_CUSTOM_FLAG_NULL = 0,
    SBR_DISCORDCHANNEL_CUSTOM_FLAG_NOT_SAFE_FOR_WORK = 1 << 0,
    SBR_DISCORDCHANNEL_CUSTOM_FLAG_MANAGED = 1 << 1
} SBR_DiscordChannel_CustomFlags;

typedef enum {
    SBR_DISCORDCHANNEL_AUTOMATIC_ARCHIVE_DURATION_60 = 60,
    SBR_DISCORDCHANNEL_AUTOMATIC_ARCHIVE_DURATION_1440 = 1440,
    SBR_DISCORDCHANNEL_AUTOMATIC_ARCHIVE_DURATION_4320 = 4320,
    SBR_DISCORDCHANNEL_AUTOMATIC_ARCHIVE_DURATION_10080 = 10080
} SBR_DiscordChannel_AutomaticArchiveDurations;

typedef enum  {
    SBR_DISCORDCHANNEL_OFFICIAL_FLAG_NULL = 0,
    SBR_DISCORDCHANNEL_OFFICIAL_FLAG_PINNED_THREAD = 1 << 1,
    SBR_DISCORDCHANNEL_OFFICIAL_FLAG_REQUIRE_THREAD_TAG = 1 << 4,
    SBR_DISCORDCHANNEL_OFFICIAL_FLAG_HIDDEN_MEDIA_DOWNLOAD_OPTIONS = 1 << 15
} SBR_DiscordChannel_OfficialFlags;

typedef enum {
    SBR_DISCORDCHANNEL_VIDEO_QUALITY_MODE_AUTO = 1,
    SBR_DISCORDCHANNEL_VIDEO_QUALITY_MODE_FULL = 2
} SBR_DiscordChannel_VideoQualityModes;

typedef struct SBR_DiscordChannel {
    SBR_Snowflake* id;
    SBR_DiscordChannel_Types type;
    SBR_Snowflake* guildId;
    int position;
    // TODO: permission_overwrites
    const char* name;
    const char* topic;
    SBR_DiscordChannel_CustomFlags customFlags;
    SBR_Snowflake* lastMessageId;
    int bitrate;
    int userLimit;
    int rateLimitPerUser;
    // TODO: recipients
    const char* iconHash;
    SBR_Snowflake* ownerId;
    SBR_Snowflake* applicationId;
    SBR_Snowflake* parentId;
    struct tm* lastPinTimestamp;
    // TODO: rtc_region
    SBR_DiscordChannel_VideoQualityModes videoQualityMode;
    int messageCount;
    // TODO: thread_metadata
    // TODO: member
    SBR_DiscordChannel_AutomaticArchiveDurations defaultAutomaticArchiveDuration;
    SBR_DiscordPermissions permissions;
    SBR_DiscordChannel_OfficialFlags officialFlags;
    int totalMessageSent;
    // TODO: available_tags
    // TODO: applied_tags
    // TODO: default_reaction_emoji
    int defaultThreadRateLimitPerUser;
    int defaultSortOrder;
    int defaultForumLayout;
    SBR_DiscordGuild* guild;
} SBR_DiscordChannel;

typedef struct SBR_DiscordMessage SBR_DiscordMessage;

SBR_DiscordChannel* SBR_DiscordChannel_Create(json_object* unparsedJsonData);

SBR_DiscordMessage* SBR_DiscordChannel_Send(const SBR_DiscordChannel* channel, const char* content, SBR_EmbedCreator_Embed* embed);
SBR_DiscordChannel* SBR_DiscordChannel_Get(const SBR_Snowflake* id);
