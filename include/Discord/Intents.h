// Purpose: Every single Discord intent
// Created on: 4/27/24 @ 11:00 PM

// Copyright (c) 2024, PortalPlayer <email@portalplayer.xyz>
// Licensed under MIT <https://opensource.org/licenses/MIT>

#pragma once

typedef enum {
    SBR_DISCORDINTENT_GUILDS = 1 << 0,
    
    /**
     * @note This one is priviledged
     */
    SBR_DISCORDINTENT_GUILD_MEMBERS = 1 << 1,
    SBR_DISCORDINTENT_GUILD_MODERATION = 1 << 2,
    SBR_DISCORDINTENT_GUILD_EMOJIS_AND_STICKERS = 1 << 3,
    SBR_DISCORDINTENT_GUILD_INTEGRATIONS = 1 << 4,
    SBR_DISCORDINTENT_GUILD_WEBHOOKS = 1 << 5,
    SBR_DISCORDINTENT_GUILD_INVITES = 1 << 6,
    SBR_DISCORDINTENT_GUILD_VOICE_STATES = 1 << 7,
    
    /**
    * @note This one is priviledged
    */
    SBR_DISCORDINTENT_GUILD_PRESENCES = 1 << 8,
    SBR_DISCORDINTENT_GUILD_MESSAGES = 1 << 9,
    SBR_DISCORDINTENT_GUILD_MESSAGE_REACTIONS = 1 << 10,
    SBR_DISCORDINTENT_GUILD_MESSAGE_TYPING = 1 << 11,
    SBR_DISCORDINTENT_DIRECT_MESSAGES = 1 << 12,
    SBR_DISCORDINTENT_DIRECT_MESSAGE_REACTIONS = 1 << 13,
    SBR_DISCORDINTENT_DIRECT_MESSAGE_TYPING = 1 << 14,
    
    /**
     * @note This one is priviledged
     */
    SBR_DISCORDINTENT_MESSAGE_CONTENT = 1 << 15,
    SBR_DISCORDINTENT_GUILD_SCHEDULED_EVENTS = 1 << 16,
    SBR_DISCORDINTENT_AUTOMATED_MODERATION_CONFIGURATION = 1 << 20,
    SBR_DISCORDINTENT_AUTOMATED_MODERATION_EXECUTION = 1 << 21,
    SBR_DISCORDINTENT_GUILD_MESSAGE_POLLS = 1 << 24,
    SBR_DISCORDINTENT_DIRECT_MESSAGE_POLLS = 1 << 25
} SBR_DiscordIntents;

SBR_DiscordIntents SBR_DiscordIntents_Get(void);

void SBR_DiscordIntents_Set(SBR_DiscordIntents intents);
void SBR_DiscordIntents_Add(SBR_DiscordIntents intents);
