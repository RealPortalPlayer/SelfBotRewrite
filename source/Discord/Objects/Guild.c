// Copyright (c) 2024, PortalPlayer <email@portalplayer.xyz>
// Licensed under MIT <https://opensource.org/licenses/MIT>

#include "Discord/Objects/Guild.h"
#include "Discord/Objects/ObjectCreatorHelpers.h"
#include "Discord/API/Events.h"

SBR_DiscordGuild* SBR_DiscordGuild_Create(json_object* unparsedJsonData) {
    SBR_OBJECTCREATORHELPERS_HEADER(SBR_DiscordGuild, "Discord guild");
    SBR_OBJECTCREATORHELPERS_GET_BOOLEAN(unavailable, "", OPTIONAL, SAME);
    SBR_OBJECTCREATORHELPERS_GET_SNOWFLAKE(id, "", REQUIRED, SAME);

    if (object->unavailable)
        SBR_OBJECTCREATORHELPERS_FOOTER();

    SBR_OBJECTCREATORHELPERS_GET_STRING(name, "", REQUIRED, SAME);
    SBR_OBJECTCREATORHELPERS_GET_STRING(iconHash, "icon", OPTIONAL, NOT_SAME);
    SBR_OBJECTCREATORHELPERS_GET_STRING(templateIconHash, "icon_hash", OPTIONAL, NOT_SAME);
    SBR_OBJECTCREATORHELPERS_GET_STRING(splashHash, "splash", OPTIONAL, NOT_SAME);
    SBR_OBJECTCREATORHELPERS_GET_STRING(discoverySplashHash, "discovery_splash", OPTIONAL, NOT_SAME);
    SBR_OBJECTCREATORHELPERS_GET_SNOWFLAKE(ownerId, "owner_id", REQUIRED, NOT_SAME);

    object->owner = SBR_DiscordUser_Get(object->ownerId);

    SBR_OBJECTCREATORHELPERS_CHECK_REQUIRED(object->owner);
    SBR_OBJECTCREATORHELPERS_GET_SNOWFLAKE(afkChannelId, "afk_channel_id", OPTIONAL, NOT_SAME);
    SBR_OBJECTCREATORHELPERS_GET_INTEGER(afkTimeoutSeconds, "afk_timeout", REQUIRED, NOT_SAME);
    SBR_OBJECTCREATORHELPERS_SET_BIT_ON_BOOLEAN(widgetEnabled, "widget_enabled", OPTIONAL, NOT_SAME, customFlags, SBR_DISCORDGUILD_CUSTOM_FLAG_WIDGETS_ENABLED);
    SBR_OBJECTCREATORHELPERS_GET_SNOWFLAKE(widgetChannelId, "widget_channel_id", OPTIONAL, NOT_SAME);
    SBR_OBJECTCREATORHELPERS_GET_INTEGER(verificationLevel, "verification_level", REQUIRED, NOT_SAME);

    // NOTE: We can get away with this because there's only two message notification types. This might not last forever
    SBR_OBJECTCREATORHELPERS_SET_BIT_ON_BOOLEAN(defaultMessageNotifications, "default_message_notifications", REQUIRED, NOT_SAME, customFlags, SBR_DISCORDGUILD_CUSTOM_FLAG_NOTIFICATIONS_MENTIONS_ONLY);
    SBR_OBJECTCREATORHELPERS_GET_INTEGER(filterLevel, "explicit_content_filter", REQUIRED, NOT_SAME);

    object->roles = NULL; // TODO
    object->emojis = NULL; // TODO
    object->features = SBR_DISCORDGUILD_FEATURE_NULL; // TODO

    // NOTE: Same as above
    SBR_OBJECTCREATORHELPERS_SET_BIT_ON_BOOLEAN(multiFactorAuthenticationLevel, "mfa_level", REQUIRED, NOT_SAME, customFlags, SBR_DISCORDGUILD_CUSTOM_FLAG_REQUIRES_MULTI_FACTOR_AUTHENTICATION);
    SBR_OBJECTCREATORHELPERS_GET_SNOWFLAKE(applicationId, "application_id", OPTIONAL, NOT_SAME);
    SBR_OBJECTCREATORHELPERS_GET_INTEGER(systemChannelFlags, "system_channel_flags", REQUIRED, NOT_SAME);
    SBR_OBJECTCREATORHELPERS_GET_SNOWFLAKE(rulesChannelId, "rules_channel_id", OPTIONAL, NOT_SAME);
    SBR_OBJECTCREATORHELPERS_GET_INTEGER(maxPresences, "max_presences", OPTIONAL, NOT_SAME);
    SBR_OBJECTCREATORHELPERS_GET_INTEGER(maxMembers, "max_members", OPTIONAL, NOT_SAME);
    SBR_OBJECTCREATORHELPERS_GET_STRING(vanityUrlCode, "vanity_url_code", OPTIONAL, NOT_SAME);
    SBR_OBJECTCREATORHELPERS_GET_STRING(description, "description", OPTIONAL, NOT_SAME);
    SBR_OBJECTCREATORHELPERS_GET_STRING(bannerHash, "banner", OPTIONAL, NOT_SAME);
    SBR_OBJECTCREATORHELPERS_GET_INTEGER(boostLevel, "premium_tier", REQUIRED, NOT_SAME);
    SBR_OBJECTCREATORHELPERS_GET_INTEGER(boostCount, "premium_subscription_count", OPTIONAL, NOT_SAME);
    SBR_OBJECTCREATORHELPERS_GET_LOCALE(preferredLocale, "preferred_locale", REQUIRED, NOT_SAME);
    SBR_OBJECTCREATORHELPERS_GET_SNOWFLAKE(publicUpdatesChannelId, "public_updates_channel_id", OPTIONAL, NOT_SAME);
    SBR_OBJECTCREATORHELPERS_GET_INTEGER(maxStageVideoChannelUsers, "max_stage_video_channel_users", OPTIONAL, NOT_SAME);
    SBR_OBJECTCREATORHELPERS_GET_INTEGER(approximateMemberCount, "approximate_member_count", OPTIONAL, NOT_SAME);
    SBR_OBJECTCREATORHELPERS_GET_INTEGER(approximatePresenceCount, "approximate_presence_count", OPTIONAL, NOT_SAME);
    // TODO: welcome_screen
    SBR_OBJECTCREATORHELPERS_GET_INTEGER(notSafeForWorkLevel, "nsfw_level", REQUIRED, NOT_SAME);

    object->stickers = NULL; // TODO

    SBR_OBJECTCREATORHELPERS_SET_BIT_ON_BOOLEAN(premiumProgressBarEnabled, "premium_progress_bar_enabled", REQUIRED, NOT_SAME, customFlags, SBR_DISCORDGUILD_CUSTOM_FLAG_PREMIUM_PROGRESS_BAR_ENABLED);
    SBR_OBJECTCREATORHELPERS_GET_SNOWFLAKE(safetyAlertsChannelId, "safety_alerts_channel_id", OPTIONAL, NOT_SAME);
    SBR_OBJECTCREATORHELPERS_FOOTER();
}

SBR_DiscordGuild* SBR_DiscordGuild_Get(const SBR_Snowflake* id) {
    return SBR_DiscordAPIEvents_GetGuild(id);
}

