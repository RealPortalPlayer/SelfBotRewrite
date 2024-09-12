// Copyright (c) 2024, PortalPlayer <email@portalplayer.xyz>
// Licensed under MIT <https://opensource.org/licenses/MIT>

#include "Discord/Objects/Guild.h"
#include "Discord/Objects/ObjectCreatorHelpers.h"
#include "Discord/API/Events.h"

SBR_DiscordGuild* SBR_DiscordGuild_Create(json_object* unparsedJsonData) {
    static BA_Boolean creatingGuild = BA_BOOLEAN_FALSE;

    if (creatingGuild)
        return NULL;

    creatingGuild = BA_BOOLEAN_TRUE;
    
    SBR_OBJECTCREATORHELPERS_HEADER(SBR_DiscordGuild, SBR_MEMORY_TYPE_GUILD, "Discord guild");
    SBR_OBJECTCREATORHELPERS_GET_BOOLEAN(unavailable, "", UNREQUIRED, SAME);
    SBR_OBJECTCREATORHELPERS_GET_SNOWFLAKE(id, "", REQUIRED, SAME);

    if (object->unavailable) {
        creatingGuild = BA_BOOLEAN_FALSE;
        SBR_OBJECTCREATORHELPERS_FOOTER();
    }

    SBR_OBJECTCREATORHELPERS_GET_STRING(name, "", REQUIRED, SAME);
    SBR_OBJECTCREATORHELPERS_GET_STRING(iconHash, "icon", UNREQUIRED, NOT_SAME);
    SBR_OBJECTCREATORHELPERS_GET_STRING(templateIconHash, "icon_hash", UNREQUIRED, NOT_SAME);
    SBR_OBJECTCREATORHELPERS_GET_STRING(splashHash, "splash", UNREQUIRED, NOT_SAME);
    SBR_OBJECTCREATORHELPERS_GET_STRING(discoverySplashHash, "discovery_splash", UNREQUIRED, NOT_SAME);
    SBR_OBJECTCREATORHELPERS_GET_SNOWFLAKE(ownerId, "owner_id", REQUIRED, NOT_SAME);

    object->owner = SBR_DiscordUser_Get(object->ownerId);

    SBR_OBJECTCREATORHELPERS_CHECK_REQUIRED(object->owner);
    SBR_OBJECTCREATORHELPERS_GET_SNOWFLAKE(afkChannelId, "afk_channel_id", UNREQUIRED, NOT_SAME);
    SBR_OBJECTCREATORHELPERS_GET_INTEGER(afkTimeoutSeconds, "afk_timeout", REQUIRED, NOT_SAME);
    SBR_OBJECTCREATORHELPERS_SET_BIT_ON_BOOLEAN(widgetEnabled, "widget_enabled", UNREQUIRED, NOT_SAME, customFlags, SBR_DISCORDGUILD_CUSTOM_FLAG_WIDGETS_ENABLED);
    SBR_OBJECTCREATORHELPERS_GET_SNOWFLAKE(widgetChannelId, "widget_channel_id", UNREQUIRED, NOT_SAME);
    SBR_OBJECTCREATORHELPERS_GET_INTEGER(verificationLevel, "verification_level", REQUIRED, NOT_SAME);

    // NOTE: We can get away with this because there's only two message notification types. This might not last forever
    SBR_OBJECTCREATORHELPERS_SET_BIT_ON_BOOLEAN(defaultMessageNotifications, "default_message_notifications", REQUIRED, NOT_SAME, customFlags, SBR_DISCORDGUILD_CUSTOM_FLAG_NOTIFICATIONS_MENTIONS_ONLY);
    SBR_OBJECTCREATORHELPERS_GET_INTEGER(filterLevel, "explicit_content_filter", REQUIRED, NOT_SAME);

    // TODO: roles
    // TODO: emojis
    // TODO: features
    // NOTE: Same as above
    SBR_OBJECTCREATORHELPERS_SET_BIT_ON_BOOLEAN(multiFactorAuthenticationLevel, "mfa_level", REQUIRED, NOT_SAME, customFlags, SBR_DISCORDGUILD_CUSTOM_FLAG_REQUIRES_MULTI_FACTOR_AUTHENTICATION);
    SBR_OBJECTCREATORHELPERS_GET_SNOWFLAKE(applicationId, "application_id", UNREQUIRED, NOT_SAME);
    SBR_OBJECTCREATORHELPERS_GET_SNOWFLAKE(systemChannelId, "system_channel_id", UNREQUIRED, NOT_SAME);
    SBR_OBJECTCREATORHELPERS_GET_INTEGER(systemChannelFlags, "system_channel_flags", REQUIRED, NOT_SAME);
    SBR_OBJECTCREATORHELPERS_GET_SNOWFLAKE(rulesChannelId, "rules_channel_id", UNREQUIRED, NOT_SAME);
    SBR_OBJECTCREATORHELPERS_GET_INTEGER(maxPresences, "max_presences", UNREQUIRED, NOT_SAME);
    SBR_OBJECTCREATORHELPERS_GET_INTEGER(maxMembers, "max_members", UNREQUIRED, NOT_SAME);
    SBR_OBJECTCREATORHELPERS_GET_STRING(vanityUrlCode, "vanity_url_code", UNREQUIRED, NOT_SAME);
    SBR_OBJECTCREATORHELPERS_GET_STRING(description, "description", UNREQUIRED, NOT_SAME);
    SBR_OBJECTCREATORHELPERS_GET_STRING(bannerHash, "banner", UNREQUIRED, NOT_SAME);
    SBR_OBJECTCREATORHELPERS_GET_INTEGER(boostLevel, "premium_tier", REQUIRED, NOT_SAME);
    SBR_OBJECTCREATORHELPERS_GET_INTEGER(boostCount, "premium_subscription_count", UNREQUIRED, NOT_SAME);
    SBR_OBJECTCREATORHELPERS_GET_LOCALE(preferredLocale, "preferred_locale", REQUIRED, NOT_SAME);
    SBR_OBJECTCREATORHELPERS_GET_SNOWFLAKE(publicUpdatesChannelId, "public_updates_channel_id", UNREQUIRED, NOT_SAME);
    SBR_OBJECTCREATORHELPERS_GET_INTEGER(maxStageVideoChannelUsers, "max_stage_video_channel_users", UNREQUIRED, NOT_SAME);
    SBR_OBJECTCREATORHELPERS_GET_INTEGER(approximateMemberCount, "approximate_member_count", UNREQUIRED, NOT_SAME);
    SBR_OBJECTCREATORHELPERS_GET_INTEGER(approximatePresenceCount, "approximate_presence_count", UNREQUIRED, NOT_SAME);
    // TODO: welcome_screen
    SBR_OBJECTCREATORHELPERS_GET_INTEGER(notSafeForWorkLevel, "nsfw_level", REQUIRED, NOT_SAME);
    // TODO: stickers
    SBR_OBJECTCREATORHELPERS_SET_BIT_ON_BOOLEAN(premiumProgressBarEnabled, "premium_progress_bar_enabled", REQUIRED, NOT_SAME, customFlags, SBR_DISCORDGUILD_CUSTOM_FLAG_PREMIUM_PROGRESS_BAR_ENABLED);
    SBR_OBJECTCREATORHELPERS_GET_SNOWFLAKE(safetyAlertsChannelId, "safety_alerts_channel_id", UNREQUIRED, NOT_SAME);

#define SBR_GUILD_GET_CHANNEL(name) \
do {                                \
    if (object->name ## Id->timestamp != SBR_SNOWFLAKE_EPOCH) { \
        object->name = SBR_DiscordChannel_Get(object->name ## Id); \
        if (object->name != NULL)   \
            object->name->guild = object; \
    }                               \
} while (BA_BOOLEAN_FALSE)

    SBR_GUILD_GET_CHANNEL(afkChannel);
    SBR_GUILD_GET_CHANNEL(widgetChannel);
    SBR_GUILD_GET_CHANNEL(systemChannel);
    SBR_GUILD_GET_CHANNEL(rulesChannel);
    SBR_GUILD_GET_CHANNEL(publicUpdatesChannel);
    
    creatingGuild = BA_BOOLEAN_FALSE;
    SBR_OBJECTCREATORHELPERS_FOOTER();
}

SBR_DiscordGuild* SBR_DiscordGuild_Get(const SBR_Snowflake* id) {
    return SBR_DiscordAPIEvents_GetGuild(id);
}

void SBR_DiscordGuild_Deallocate(SBR_DiscordGuild* guild) {
    if (guild == NULL)
        return;
    
    SBR_OBJECTCREATORHELPERS_DEALLOCATE_SNOWFLAKE(guild->id);
    SBR_OBJECTCREATORHELPERS_DEALLOCATE_USER(guild->owner);
    SBR_OBJECTCREATORHELPERS_DEALLOCATE_SNOWFLAKE(guild->ownerId);
    SBR_OBJECTCREATORHELPERS_DEALLOCATE_SNOWFLAKE(guild->afkChannelId);
    SBR_OBJECTCREATORHELPERS_DEALLOCATE_SNOWFLAKE(guild->widgetChannelId);
    // TODO: roles
    // TODO: emojis
    SBR_OBJECTCREATORHELPERS_DEALLOCATE_SNOWFLAKE(guild->applicationId);
    SBR_OBJECTCREATORHELPERS_DEALLOCATE_SNOWFLAKE(guild->systemChannelId);
    SBR_OBJECTCREATORHELPERS_DEALLOCATE_SNOWFLAKE(guild->rulesChannelId);
    SBR_OBJECTCREATORHELPERS_DEALLOCATE_SNOWFLAKE(guild->publicUpdatesChannelId);
    // TODO: welcomeScreen
    // TODO: stickers
    SBR_OBJECTCREATORHELPERS_DEALLOCATE_SNOWFLAKE(guild->safetyAlertsChannelId);

#define SBR_DISCORDGUILD_DEALLOCATE_CHANNEL(variable) \
do {                                                  \
    if (variable != NULL) {                           \
        variable->guild = NULL;                       \
        SBR_OBJECTCREATORHELPERS_DEALLOCATE_CHANNEL(variable); \
    }                                                 \
} while (BA_BOOLEAN_FALSE)

    SBR_DISCORDGUILD_DEALLOCATE_CHANNEL(guild->afkChannel);
    SBR_DISCORDGUILD_DEALLOCATE_CHANNEL(guild->widgetChannel);
    SBR_DISCORDGUILD_DEALLOCATE_CHANNEL(guild->systemChannel);
    SBR_DISCORDGUILD_DEALLOCATE_CHANNEL(guild->rulesChannel);
    SBR_DISCORDGUILD_DEALLOCATE_CHANNEL(guild->publicUpdatesChannel);
    SBR_OBJECTCREATORHELPERS_DEALLOCATE_MANUAL(guild, sizeof(SBR_DiscordGuild), SBR_MEMORY_TYPE_GUILD);
}
