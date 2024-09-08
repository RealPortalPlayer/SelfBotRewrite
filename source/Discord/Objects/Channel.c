// Copyright (c) 2024, PortalPlayer <email@portalplayer.xyz>
// Licensed under MIT <https://opensource.org/licenses/MIT>

#include "Discord/Objects/Channel.h"
#include "Discord/API/Events.h"
#include "Discord/Objects/ObjectCreatorHelpers.h"

SBR_DiscordChannel* SBR_DiscordChannel_Create(json_object* unparsedJsonData) {
    SBR_OBJECTCREATORHELPERS_HEADER(SBR_DiscordChannel, "Discord channel");
    SBR_OBJECTCREATORHELPERS_GET_SNOWFLAKE(id, "", REQUIRED, SAME);
    SBR_OBJECTCREATORHELPERS_GET_INTEGER(type, "", REQUIRED, SAME);
    SBR_OBJECTCREATORHELPERS_GET_SNOWFLAKE(guildId, "guild_id", OPTIONAL, NOT_SAME);
    SBR_OBJECTCREATORHELPERS_GET_INTEGER(position, "", OPTIONAL, SAME);
    // TODO: permission_overwrites
    SBR_OBJECTCREATORHELPERS_GET_STRING(name, "", OPTIONAL, SAME);
    SBR_OBJECTCREATORHELPERS_GET_STRING(topic, "", OPTIONAL, SAME);
    SBR_OBJECTCREATORHELPERS_SET_BIT_ON_BOOLEAN(notSafeForWork, "nsfw", OPTIONAL, NOT_SAME, customFlags, SBR_DISCORDCHANNEL_CUSTOM_FLAG_NOT_SAFE_FOR_WORK);
    SBR_OBJECTCREATORHELPERS_GET_SNOWFLAKE(lastMessageId, "last_message_id", OPTIONAL, NOT_SAME);
    SBR_OBJECTCREATORHELPERS_GET_INTEGER(bitrate, "", OPTIONAL, SAME);
    SBR_OBJECTCREATORHELPERS_GET_INTEGER(userLimit, "user_limit", OPTIONAL, NOT_SAME);
    SBR_OBJECTCREATORHELPERS_GET_INTEGER(rateLimitPerUser, "rate_limit_per_user", OPTIONAL, NOT_SAME);
    // TODO: recipients
    SBR_OBJECTCREATORHELPERS_GET_STRING(iconHash, "icon", OPTIONAL, NOT_SAME);
    SBR_OBJECTCREATORHELPERS_GET_SNOWFLAKE(ownerId, "owner_id", OPTIONAL, NOT_SAME);
    SBR_OBJECTCREATORHELPERS_GET_SNOWFLAKE(applicationId, "application_id", OPTIONAL, NOT_SAME);
    SBR_OBJECTCREATORHELPERS_SET_BIT_ON_BOOLEAN(managed, "", OPTIONAL, SAME, customFlags, SBR_DISCORDCHANNEL_CUSTOM_FLAG_MANAGED);
    SBR_OBJECTCREATORHELPERS_GET_SNOWFLAKE(parentId, "parent_id", OPTIONAL, NOT_SAME);
    // TODO: last_pin_timestamp
    // TODO: rtc_region
    SBR_OBJECTCREATORHELPERS_GET_INTEGER(videoQualityMode, "video_qulity_mode", OPTIONAL, NOT_SAME);
    SBR_OBJECTCREATORHELPERS_GET_INTEGER(messageCount, "message_count", OPTIONAL, NOT_SAME);
    // TODO: thread_metadata
    // TODO: member
    SBR_OBJECTCREATORHELPERS_GET_INTEGER(defaultAutomaticArchiveDuration, "default_auto_archive_duration", OPTIONAL, NOT_SAME);
    SBR_OBJECTCREATORHELPERS_GET_PERMISSIONS(permissions, "", OPTIONAL, SAME);
    SBR_OBJECTCREATORHELPERS_GET_INTEGER(officialFlags, "flags", OPTIONAL, NOT_SAME);
    SBR_OBJECTCREATORHELPERS_GET_INTEGER(totalMessageSent, "total_message_sent", OPTIONAL, NOT_SAME);
    // TODO: available_tags
    // TODO: applied_tags
    // TODO: default_reaction_emoji
    SBR_OBJECTCREATORHELPERS_GET_INTEGER(defaultThreadRateLimitPerUser, "default_thread_rate_limit_per_user", OPTIONAL, NOT_SAME);
    SBR_OBJECTCREATORHELPERS_GET_INTEGER(defaultSortOrder, "default_sort_order", OPTIONAL, NOT_SAME);
    SBR_OBJECTCREATORHELPERS_GET_INTEGER(defaultForumLayout, "default_forum_layout", OPTIONAL, NOT_SAME);

    // TODO: Turn into own macro
    if (object->type == SBR_DISCORDCHANNEL_TYPE_GUILD_TEXT) {
        object->guild = SBR_DiscordGuild_Get(object->guildId);

        SBR_OBJECTCREATORHELPERS_CHECK_REQUIRED(object->guild);
    }

    SBR_OBJECTCREATORHELPERS_FOOTER();
}

SBR_DiscordMessage* SBR_DiscordChannel_Send(const SBR_DiscordChannel* channel, const char* content, SBR_EmbedCreator_Embed* embed) {
    if (channel == NULL) {
        BA_LOGGER_ERROR("Channel is null\n");
        return NULL;
    }
    
    if (channel->type == SBR_DISCORDCHANNEL_TYPE_GUILD_CATEGORY || channel->type == SBR_DISCORDCHANNEL_TYPE_GUILD_DIRECTORY || channel->type == SBR_DISCORDCHANNEL_TYPE_GUILD_MEDIA) {
        BA_LOGGER_ERROR("Invalid channel: the specified channel doesn't accept messages (%i)\n", channel->type);
        return NULL;
    }

    // TODO: Check permissions
    return SBR_DiscordAPIEvents_SendMessage(channel->id, content, embed);
}

SBR_DiscordChannel* SBR_DiscordChannel_Get(const SBR_Snowflake* id) {
    return SBR_DiscordAPIEvents_GetChannel(id);
}
