// Copyright (c) 2024, PortalPlayer <email@portalplayer.xyz>
// Licensed under MIT <https://opensource.org/licenses/MIT>

// Purpose: Discord application. Bread and butter of a Discord bot
// Created on: 4/27/24 @ 12:34 AM

#pragma once

#include <json_object.h>
#include <BaconAPI/Internal/Boolean.h>

#include "Snowflake.h"
#include "User.h"
#include "Guild.h"

typedef enum {
    /**
     * Application uses auto moderation API
     */
    SBR_DISCORDAPPLICATION_FLAG_AUTO_MODERATION = 1 << 6,

    /**
     * Allow to receive presence update events. Requires the bot to be in 100 guilds or more, and be verified.
     * Non-verified bots use the limited version
     */
    SBR_DISCORDAPPLICATION_FLAG_GATEWAY_PRESENCE = 1 << 12,

    /**
     * Allow to receive presence update events
     */
    SBR_DISCORDAPPLICATION_FLAG_GATEWAY_PRESENCE_LIMITED = 1 << 13,

    /**
     * Allow to receive member events. Requires the bot to be in 100 guilds or more, and be verified.
     * Non-verified bots use the limied version
     */
    SBR_DISCORDAPPLICATION_FLAG_GATEWAY_GUILD_MEMBERS = 1 << 14,

    /**
     * Allow to receive member events
     */
    SBR_DISCORDAPPLICATION_FLAG_GATEWAY_GUILD_MEMBERS_LIMITED = 1 << 15,

    /**
     * Bot verification prevented due to unusual app growth
     */
    SBR_DISCORDAPPLICATION_FLAG_VERIFICATION_PENDING_GUILD_LIMIT = 1 << 16,

    /**
     * @note Not normally available
     */
    SBR_DISCORDAPPLICATION_FLAG_EMBEDDED_INTO_CLIENT = 1 << 17,

    /**
     * Allow to receive message content. Requires the bot to be in 100 guilds or more, and be verified.
     * Non-verified bots use the limied version
     */
    SBR_DISCORDAPPLICATION_FLAG_GATEWAY_MESSAGE_CONTENT = 1 << 18,

    /**
     * Allow to receive message content
     */
    SBR_DISCORDAPPLICATION_FLAG_GATEWAY_MESSAGE_CONTENT_LIMITED = 1 << 19,
    SBR_DISCORDAPPLICATION_FLAG_REGISTERED_COMMANDS = 1 << 23
} SBR_DiscordApplication_OfficialFlags;

typedef enum {
     /**
     * Can the bot be added by other users
     */
    SBR_DISCORDAPPLICATION_CUSTOM_FLAG_BOT_PUBLIC = 1 << 0,

     /**
     * The bot requires a OAuth2 grant to join a guild
     */
    SBR_DISCORDAPPLICATION_CUSTOM_FLAG_BOT_REQUIRES_GRANT = 1 << 1
} SBR_DiscordApplication_CustomFlags;

typedef struct {
    SBR_Snowflake* id;
    const char* name;
    const char* iconHash;
    const char* description;
    // TODO: RPC is closed beta (rpc_origins)
    SBR_DiscordApplication_CustomFlags customFlags;
    SBR_DiscordUser* bot;
    const char* termsOfServiceUrl;
    const char* privacyPolicyUrl;
    SBR_DiscordUser* owner;
    const char* verifyKey;
    // TODO: team
    SBR_Snowflake* guildId;
    SBR_DiscordGuild* guild;
    SBR_Snowflake* primarySkuId;
    const char* storeSlug;
    const char* richPresenceCoverImage;
    SBR_DiscordApplication_OfficialFlags officialFlags;
    int approximateGuildCount;
    json_object* redirectUris;
    const char* interactionsEndpointUrl;
    const char* roleConnectionsVerificationUrl;
    json_object* tags;
    // TODO: install_params
    json_object* integrationTypesConfiguration;
    const char* customInstallationUrl;
} SBR_DiscordApplication;

SBR_DiscordApplication* SBR_DiscordApplication_Create(json_object* applicationData);
void SBR_DiscordApplication_Deallocate(SBR_DiscordApplication* application);
