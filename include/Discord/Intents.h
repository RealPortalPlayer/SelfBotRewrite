// Purpose: Every single Discord intent
// Created on: 4/27/24 @ 11:00 PM

// Copyright (c) 2024, PortalPlayer <email@portalplayer.xyz>
// Licensed under MIT <https://opensource.org/licenses/MIT>

#pragma once

typedef enum {
    /**
     * Enables: GUILD_CREATE, GUILD_UPDATE, GUILD_DELETE, GUILD_ROLE_CREATE, GUILD_ROLE_UPDATE, GUILD_ROLE_DELETE, CHANNEL_CREATE,
     * CHANNEL_UPDATE, CHANNEL_DELETE, CHANNEL_PINS_UPDATE, THREAD_CREATE, THREAD_UPDATE, THREAD_DELETE, THREAD_LIST_SYNC,
     * THREAD_MEMBER_UPDATE, THREAD_MEMBER_UPDATE, STAGE_INSTANCE_CREATE, STAGE_INSTANCE_UPDATE, and STAGE_INSTANCE_DELETE
     */
    SBR_DISCORDINTENT_GUILDS = 1 << 0,
    
    /**
     * Enables: GUILD_MEMBER_ADD, GUILD_MEMBER_UPDATE, GUILD_MEMBER_REMOVE, and THREAD_MEMBERS_UPDATE
     * @note This one is privileged
     */
    SBR_DISCORDINTENT_GUILD_MEMBERS = 1 << 1,

    /**
     * Enables: GUILD_AUDIT_LOG_ENTRY_CREATE, GUILD_BAN_ADD, and GUILD_BAN_REMOVE
     */
    SBR_DISCORDINTENT_GUILD_MODERATION = 1 << 2,

    /**
     * Enables: GUILD_EMOJIS_UPDATE, and GUILD_STICKERS_UPDATE
     */
    SBR_DISCORDINTENT_GUILD_EMOJIS_AND_STICKERS = 1 << 3,

    /**
     * Enables: GUILD_INTEGRATIONS_UPDATE, INTEGRATION_CREATE, INTEGRATION_UPDATE, and INTEGRATION_DELETE
     */
    SBR_DISCORDINTENT_GUILD_INTEGRATIONS = 1 << 4,

    /**
     * Enables: WEBHOOKS_UPDATE
     */
    SBR_DISCORDINTENT_GUILD_WEBHOOKS = 1 << 5,

    /**
     * Enables: INVITE_CREATE, and INVITE_DELETE
     */
    SBR_DISCORDINTENT_GUILD_INVITES = 1 << 6,

    /**
     * Enables: VOICE_STATE_UPDATE
     */
    SBR_DISCORDINTENT_GUILD_VOICE_STATES = 1 << 7,
    
    /**
     * Enables: PRESENCE_UPDATE
     * @note This one is privileged
     */
    SBR_DISCORDINTENT_GUILD_PRESENCES = 1 << 8,
    
    /**
     * Enables: MESSAGE_CREATE, MESSAGE_UPDATE, MESSAGE_DELETE, and MESSAGE_DELETE_BULK
     */
    SBR_DISCORDINTENT_GUILD_MESSAGES = 1 << 9,
    
    /**
     * Enables: MESSAGE_REACTION_ADD, MESSAGE_REACTION_REMOVE, MESSAGE_REACTION_REMOVE_ALL, and MESSAGE_REACTION_REMOVE_EMOJI
     */
    SBR_DISCORDINTENT_GUILD_MESSAGE_REACTIONS = 1 << 10,
    
    /**
     * Enables: TYPING_START
     */
    SBR_DISCORDINTENT_GUILD_MESSAGE_TYPING = 1 << 11,
    
    /**
     * Enables: MESSAGE_CREATE, MESSAGE_UPDATE, MESSAGE_DELETE, and CHANNEL_PINS_UPDATE
     */
    SBR_DISCORDINTENT_DIRECT_MESSAGES = 1 << 12,
    
    /**
     * Enables: MESSAGE_REACTION_ADD, MESSAGE_REACTION_REMOVE, MESSAGE_REACTION_REMOVE_ALL, and MESSAGE_REACTION_REMOVE_EMOJI
     */
    SBR_DISCORDINTENT_DIRECT_MESSAGE_REACTIONS = 1 << 13,
    
    /**
     * Enables: TYPING_START
     */
    SBR_DISCORDINTENT_DIRECT_MESSAGE_TYPING = 1 << 14,
    
    /**
     * This doesn't enable any events
     * @note This one is privileged
     */
    SBR_DISCORDINTENT_MESSAGE_CONTENT = 1 << 15,

     /**
     * Enables: GUILD_SCHEDULED_EVENT_CREATE, GUILD_SCHEDULED_EVENT_UPDATE, GUILD_SCHEDULED_EVENT_DELETE, GUILD_SCHEDULED_EVENT_USER_ADD, and
     * GUILD_SCHEDULED_EVENT_USER_REMOVE
     */
    SBR_DISCORDINTENT_GUILD_SCHEDULED_EVENTS = 1 << 16,

    /**
     * Enables: AUTO_MODERATION_RULE_CREATE, AUTO_MODERATION_RULE_UPDATE, and AUTO_MODERATION_RULE_DELETE
     */
    SBR_DISCORDINTENT_AUTOMATED_MODERATION_CONFIGURATION = 1 << 20,

    /**
     * Enables: AUTO_MODERATION_ACTION_EXECUTION
     */
    SBR_DISCORDINTENT_AUTOMATED_MODERATION_EXECUTION = 1 << 21,

    /**
     * Enables: MESSAGE_POLL_VOTE_ADD, and MESSAGE_POLL_VOTE_REMOVE
     */
    SBR_DISCORDINTENT_GUILD_MESSAGE_POLLS = 1 << 24,

    /**
     * Enables: MESSAGE_POLL_VOTE_ADD, and MESSAGE_POLL_VOTE_REMOVE
     */
    SBR_DISCORDINTENT_DIRECT_MESSAGE_POLLS = 1 << 25
} SBR_DiscordIntents;

SBR_DiscordIntents SBR_DiscordIntents_Get(void);

void SBR_DiscordIntents_Set(SBR_DiscordIntents intents);
void SBR_DiscordIntents_Add(SBR_DiscordIntents intents);
