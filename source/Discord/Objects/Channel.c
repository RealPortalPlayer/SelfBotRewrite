// Copyright (c) 2024, PortalPlayer <email@portalplayer.xyz>
// Licensed under MIT <https://opensource.org/licenses/MIT>

#include "Discord/Objects/Channel.h"
#include "Discord/API/Events.h"
#include "Discord/Objects/ObjectCreatorHelpers.h"

SBR_DiscordChannel* SBR_DiscordChannel_Create(json_object* unparsedJsonData) {
    SBR_OBJECTCREATORHELPERS_HEADER(SBR_DiscordChannel, SBR_MEMORY_TYPE_CHANNEL, "Discord channel");
    SBR_OBJECTCREATORHELPERS_GET_SNOWFLAKE(id, "", REQUIRED, SAME);
    SBR_OBJECTCREATORHELPERS_GET_INTEGER(type, "", REQUIRED, SAME);
    SBR_OBJECTCREATORHELPERS_GET_SNOWFLAKE(guildId, "guild_id", UNREQUIRED, NOT_SAME);
    SBR_OBJECTCREATORHELPERS_GET_INTEGER(position, "", UNREQUIRED, SAME);
    // TODO: permission_overwrites
    SBR_OBJECTCREATORHELPERS_GET_STRING(name, "", UNREQUIRED, SAME);
    SBR_OBJECTCREATORHELPERS_GET_STRING(topic, "", UNREQUIRED, SAME);
    SBR_OBJECTCREATORHELPERS_SET_BIT_ON_BOOLEAN(notSafeForWork, "nsfw", UNREQUIRED, NOT_SAME, customFlags, SBR_DISCORDCHANNEL_CUSTOM_FLAG_NOT_SAFE_FOR_WORK);
    SBR_OBJECTCREATORHELPERS_GET_SNOWFLAKE(lastMessageId, "last_message_id", UNREQUIRED, NOT_SAME);
    SBR_OBJECTCREATORHELPERS_GET_INTEGER(bitrate, "", UNREQUIRED, SAME);
    SBR_OBJECTCREATORHELPERS_GET_INTEGER(userLimit, "user_limit", UNREQUIRED, NOT_SAME);
    SBR_OBJECTCREATORHELPERS_GET_INTEGER(rateLimitPerUser, "rate_limit_per_user", UNREQUIRED, NOT_SAME);
    // TODO: recipients
    SBR_OBJECTCREATORHELPERS_GET_STRING(iconHash, "icon", UNREQUIRED, NOT_SAME);
    SBR_OBJECTCREATORHELPERS_GET_SNOWFLAKE(ownerId, "owner_id", UNREQUIRED, NOT_SAME);
    SBR_OBJECTCREATORHELPERS_GET_SNOWFLAKE(applicationId, "application_id", UNREQUIRED, NOT_SAME);
    SBR_OBJECTCREATORHELPERS_SET_BIT_ON_BOOLEAN(managed, "", UNREQUIRED, SAME, customFlags, SBR_DISCORDCHANNEL_CUSTOM_FLAG_MANAGED);
    SBR_OBJECTCREATORHELPERS_GET_SNOWFLAKE(parentId, "parent_id", UNREQUIRED, NOT_SAME);
    SBR_OBJECTCREATORHELPERS_GET_TIME(lastPinTimestamp, "last_pin_timestamp", UNREQUIRED, NOT_SAME);
    // TODO: rtc_region
    SBR_OBJECTCREATORHELPERS_GET_INTEGER(videoQualityMode, "video_qulity_mode", UNREQUIRED, NOT_SAME);
    SBR_OBJECTCREATORHELPERS_GET_INTEGER(messageCount, "message_count", UNREQUIRED, NOT_SAME);
    // TODO: thread_metadata
    // TODO: member
    SBR_OBJECTCREATORHELPERS_GET_INTEGER(defaultAutomaticArchiveDuration, "default_auto_archive_duration", UNREQUIRED, NOT_SAME);
    SBR_OBJECTCREATORHELPERS_GET_PERMISSIONS(permissions, "", UNREQUIRED, SAME);
    SBR_OBJECTCREATORHELPERS_GET_INTEGER(officialFlags, "flags", UNREQUIRED, NOT_SAME);
    SBR_OBJECTCREATORHELPERS_GET_INTEGER(totalMessageSent, "total_message_sent", UNREQUIRED, NOT_SAME);
    // TODO: available_tags
    // TODO: applied_tags
    // TODO: default_reaction_emoji
    SBR_OBJECTCREATORHELPERS_GET_INTEGER(defaultThreadRateLimitPerUser, "default_thread_rate_limit_per_user", UNREQUIRED, NOT_SAME);
    SBR_OBJECTCREATORHELPERS_GET_INTEGER(defaultSortOrder, "default_sort_order", UNREQUIRED, NOT_SAME);
    SBR_OBJECTCREATORHELPERS_GET_INTEGER(defaultForumLayout, "default_forum_layout", UNREQUIRED, NOT_SAME);

    if (object->type == SBR_DISCORDCHANNEL_TYPE_GUILD_TEXT)
        SBR_OBJECTCREATORHELPERS_GRAB_GUILD(guild, UNREQUIRED);

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

void SBR_DiscordChannel_Deallocate(SBR_DiscordChannel* channel) {
    if (channel == NULL)
        return;
    
    SBR_OBJECTCREATORHELPERS_DEALLOCATE_SNOWFLAKE(channel->id);
    SBR_OBJECTCREATORHELPERS_DEALLOCATE_SNOWFLAKE(channel->guildId);
    SBR_OBJECTCREATORHELPERS_DEALLOCATE_SNOWFLAKE(channel->lastMessageId);
    SBR_OBJECTCREATORHELPERS_DEALLOCATE_SNOWFLAKE(channel->ownerId);
    SBR_OBJECTCREATORHELPERS_DEALLOCATE_SNOWFLAKE(channel->applicationId);
    SBR_OBJECTCREATORHELPERS_DEALLOCATE_SNOWFLAKE(channel->parentId);
    SBR_OBJECTCREATORHELPERS_DEALLOCATE_TIME(channel->lastPinTimestamp);
    SBR_OBJECTCREATORHELPERS_DEALLOCATE_GUILD(channel->guild);
    SBR_OBJECTCREATORHELPERS_DEALLOCATE_MANUAL(channel, sizeof(SBR_DiscordChannel), SBR_MEMORY_TYPE_CHANNEL);
}
