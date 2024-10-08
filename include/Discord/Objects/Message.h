// Purpose: Discord message
// Created on: 4/27/24 @ 5:35 PM

// Copyright (c) 2024, PortalPlayer <email@portalplayer.xyz>
// Licensed under MIT <https://opensource.org/licenses/MIT>

#pragma once

#include <BaconAPI/Storage/DynamicArray.h>
#include <time.h>

#include "Snowflake.h"
#include "User.h"
#include "Application.h"
#include "Channel.h"

typedef enum {
    SBR_DISCORDMESSAGE_CUSTOM_FLAG_NULL = 0,
    SBR_DISCORDMESSAGE_CUSTOM_FLAG_TEXT_TO_SPEECH = 1 << 0,
    SBR_DISCORDMESSAGE_CUSTOM_FLAG_MENTIONS_EVERYONE = 1 << 1,
    SBR_DISCORDMESSAGE_CUSTOM_FLAG_PINNED = 1 << 2
} SBR_DiscordMessage_CustomFlags;

typedef enum {
    SBR_DISCORDMESSAGE_TYPE_DEFAULT = 0,
    SBR_DISCORDMESSAGE_TYPE_RECIPIENT_ADDED,
    SBR_DISCORDMESSAGE_TYPE_RECIPIENT_REMOVED,
    SBR_DISCORDMESSAGE_TYPE_CALL,
    SBR_DISCORDMESSAGE_TYPE_CHANNEL_NAME_CHANGED,
    SBR_DISCORDMESSAGE_TYPE_CHANNEL_ICON_CHANGED,
    SBR_DISCORDMESSAGE_TYPE_CHANNEL_PINNED_MESSAGE,
    SBR_DISCORDMESSAGE_TYPE_USER_JOIN,
    SBR_DISCORDMESSAGE_TYPE_GUILD_BOOSTED,
    SBR_DISCORDMESSAGE_TYPE_GUILD_ACHIEVED_GUILD_BOOST_TIER_1,
    SBR_DISCORDMESSAGE_TYPE_GUILD_ACHIEVED_GUILD_BOOST_TIER_2,
    SBR_DISCORDMESSAGE_TYPE_GUILD_ACHIEVED_GUILD_BOOST_TIED_3,
    SBR_DISCORDMESSAGE_TYPE_CHANNEL_FOLLOR_ADDED,
    SBR_DISCORDMESSAGE_TYPE_GUILD_DISCOVERY_DISQUALIFIED,
    SBR_DISCORDMESSAGE_TYPE_GUILD_DISCOVERY_REQUALIFIED,
    SBR_DISCORDMESSAGE_TYPE_GUILD_DISCOVERY_GRACE_PERIOD_INITIAL_WARNING,
    SBR_DISCORDMESSAGE_TYPE_GUILD_DISCOVERY_GRACE_PERIOD_FINAL_WARNING,
    SBR_DISCORDMESSAGE_TYPE_THREAD_CREATED,
    SBR_DISCORDMESSAGE_TYPE_REPLY,
    SBR_DISCORDMESSAGE_TYPE_CHAT_INPUT_COMMAND,
    SBR_DISCORDMESSAGE_TYPE_THREAD_STARTER_MESSAGE,
    SBR_DISCORDMESSAGE_TYPE_GUILD_INVITE_REMINDER,
    SBR_DISCORDMESSAGE_TYPE_CONTEXT_MENU_COMMAND,
    SBR_DISCORDMESSAGE_TYPE_AUTOMATIC_MODERATION_ACTION,
    SBR_DISCORDMESSAGE_TYPE_ROLE_SUBSCRIPTION_PURCHASED,
    SBR_DISCORDMESSAGE_TYPE_INTERACTION_PREMIUM_UPSELL,
    SBR_DISCORDMESSAGE_TYPE_STAGE_STARTED,
    SBR_DISCORDMESSAGE_TYPE_STAGE_ENDED,
    SBR_DISCORDMESSAGE_TYPE_STAGE_SPEAKER,
    SBR_DISCORDMESSAGE_TYPE_STAGE_TOPIC,
    SBR_DISCORDMESSAGE_TYPE_GUILD_APPLICATION_PREMIUM_SUBSCRIPTION
} SBR_DiscordMessage_Types;

typedef enum {
    SBR_DISCORDMESSAGE_OFFICIAL_FLAG_CROSSPOSTED = 1 << 0,
    SBR_DISCORDMESSAGE_OFFICIAL_FLAG_IS_CROSSPOST = 1 << 1,
    SBR_DISCORDMESSAGE_OFFICIAL_FLAG_SUPPRESS_EMBEDS = 1 << 2,
    SBR_DISCORDMESSAGE_OFFICIAL_FLAG_SOURCE_MESSAGE_DELETED = 1 << 3,
    SBR_DISCORDMESSAGE_OFFICIAL_FLAG_URGENT = 1 << 4,
    SBR_DISCORDMESSAGE_OFFICIAL_FLAG_HAS_THREAD = 1 << 5,
    SBR_DISCORDMESSAGE_OFFICIAL_FLAG_EPHEMERAL = 1 << 6,
    SBR_DISCORDMESSAGE_OFFICIAL_FLAG_LOADING = 1 << 7,
    SBR_DISCORDMESSAGE_OFFICIAL_FLAG_FAILED_TO_MENTION_SOME_ROLES_IN_THREAD = 1 << 8,
    SBR_DISCORDMESSAGE_OFFICIAL_FLAG_SUPPRESS_NOTIFICATIONS = 1 << 12,
    SBR_DISCORDMESSAGE_OFFICIAL_FLAG_IS_VOICE_MESSAGE = 1 << 13
} SBR_DiscordMessage_OfficialFlags;

typedef struct SBR_DiscordMessage {
    SBR_Snowflake* id;
    SBR_Snowflake* channelId;
    SBR_DiscordChannel* channel;
    SBR_DiscordUser* author;

    /**
     * @warning Will always be NULL if you don't set the intent SBR_DISCORDINTENT_MESSAGE_CONTENT
     * @deprecated Rumors of it potentially getting removed in the future
     */
    const char* content;
    struct tm* timestamp;
    struct tm* editedTimestamp;
    SBR_DiscordMessage_CustomFlags customFlags;
    struct {
        BA_DynamicArray* users;
        BA_DynamicArray* roles;
        BA_DynamicArray* channels;
    } mentions;

    /**
     * @deprecated Rumors of it potentially getting removed in the future
     */
    BA_DynamicArray* attachments;

    /**
     * @deprecated Rumors of it potentially getting removed in the future
     */
    BA_DynamicArray* embeds;
    BA_DynamicArray* reactions;
    const char* nonce;
    SBR_Snowflake* webhookId;
    SBR_DiscordMessage_Types type;
    // TODO: activity
    SBR_DiscordApplication* application;
    SBR_Snowflake* applicationId;
    // TODO: message_reference
    SBR_DiscordMessage_OfficialFlags officialFlags;
    struct SBR_DiscordMessage* referencedMessage;
    // TODO: interaction_metadata
    SBR_DiscordChannel* thread;

    /**
     * @deprecated Rumors of it potentially getting removed in the future
     */
    BA_DynamicArray* components;
    BA_DynamicArray* stickerItems;
    int position;
    // TODO: role_subscription_data
    // TODO: resolved
    // TODO: poll
    // TODO: call
} SBR_DiscordMessage;

SBR_DiscordMessage* SBR_DiscordMessage_Create(json_object* unparsedJsonData);

void SBR_DiscordMessage_Deallocate(SBR_DiscordMessage* message);
