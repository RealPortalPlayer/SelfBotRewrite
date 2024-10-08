// Copyright (c) 2024, PortalPlayer <email@portalplayer.xyz>
// Licensed under MIT <https://opensource.org/licenses/MIT>

#include "Discord/Objects/Message.h"
#include "Discord/Objects/ObjectCreatorHelpers.h"

SBR_DiscordMessage* SBR_DiscordMessage_Create(json_object* unparsedJsonData) {
    SBR_OBJECTCREATORHELPERS_HEADER(SBR_DiscordMessage, SBR_MEMORY_TYPE_MESSAGE, "Discord message");
    SBR_OBJECTCREATORHELPERS_GET_SNOWFLAKE(id, "", REQUIRED, SAME);
    SBR_OBJECTCREATORHELPERS_GET_SNOWFLAKE(channelId, "channel_id", REQUIRED, NOT_SAME);

    object->channel = SBR_DiscordChannel_Get(object->channelId);
    
    SBR_OBJECTCREATORHELPERS_GET_USER(author, "", REQUIRED, SAME);
    SBR_OBJECTCREATORHELPERS_GET_STRING(content, "", REQUIRED, SAME);
    SBR_OBJECTCREATORHELPERS_GET_TIME(timestamp, "", REQUIRED, SAME);
    SBR_OBJECTCREATORHELPERS_GET_TIME(editedTimestamp, "edited_timestamp", UNREQUIRED, NOT_SAME);
    SBR_OBJECTCREATORHELPERS_SET_BIT_ON_BOOLEAN(textToSpeech, "tts", REQUIRED, NOT_SAME, customFlags, SBR_DISCORDMESSAGE_CUSTOM_FLAG_TEXT_TO_SPEECH);
    SBR_OBJECTCREATORHELPERS_SET_BIT_ON_BOOLEAN(mentionEveryone, "mention_everyone", REQUIRED, NOT_SAME, customFlags, SBR_DISCORDMESSAGE_CUSTOM_FLAG_MENTIONS_EVERYONE);
    // TODO: mentions
    // TODO: mentions_roles
    // TODO: mentions_channels
    // TODO: attachments
    // TODO: embeds
    // TODO: reactions
    SBR_OBJECTCREATORHELPERS_GET_STRING(nonce, "", UNREQUIRED, SAME);
    SBR_OBJECTCREATORHELPERS_SET_BIT_ON_BOOLEAN(pinned, "", REQUIRED, SAME, customFlags, SBR_DISCORDMESSAGE_CUSTOM_FLAG_PINNED);
    SBR_OBJECTCREATORHELPERS_GET_SNOWFLAKE(webhookId, "webhook_id", UNREQUIRED, NOT_SAME);
    SBR_OBJECTCREATORHELPERS_GET_INTEGER(type, "", REQUIRED, SAME);
    // TODO: activity
    SBR_OBJECTCREATORHELPERS_GET_APPLICATION(application, "", UNREQUIRED, SAME);
    SBR_OBJECTCREATORHELPERS_GET_SNOWFLAKE(applicationId, "application_id", UNREQUIRED, NOT_SAME);
    // TODO: message_reference
    SBR_OBJECTCREATORHELPERS_GET_INTEGER(officialFlags, "flags", UNREQUIRED, NOT_SAME);
    // TODO: referenced_message
    // TODO: interaction_metadata
    // TODO: thread
    // TODO: components
    // TODO: sticker_items
    SBR_OBJECTCREATORHELPERS_GET_INTEGER(position, "", UNREQUIRED, SAME);
    // TODO: role_subscription_date
    // TODO: resolved
    // TODO: poll
    SBR_OBJECTCREATORHELPERS_FOOTER();
}

void SBR_DiscordMessage_Deallocate(SBR_DiscordMessage* message) {
    if (message == NULL)
        return;
    
    SBR_OBJECTCREATORHELPERS_DEALLOCATE_SNOWFLAKE(message->id);
    SBR_OBJECTCREATORHELPERS_DEALLOCATE_SNOWFLAKE(message->channelId);
    SBR_OBJECTCREATORHELPERS_DEALLOCATE_CHANNEL(message->channel);
    SBR_OBJECTCREATORHELPERS_DEALLOCATE_USER(message->author);
    SBR_OBJECTCREATORHELPERS_DEALLOCATE_TIME(message->timestamp);
    SBR_OBJECTCREATORHELPERS_DEALLOCATE_TIME(message->editedTimestamp);
    // TODO: users
    // TODO: mentions_roles
    // TODO: mentions_channels
    // TODO: attachments
    // TODO: embeds
    // TODO: reactions
    SBR_OBJECTCREATORHELPERS_DEALLOCATE_SNOWFLAKE(message->webhookId);
    SBR_OBJECTCREATORHELPERS_DEALLOCATE_APPLICATION(message->application);
    SBR_OBJECTCREATORHELPERS_DEALLOCATE_SNOWFLAKE(message->applicationId);
    // TODO: message_reference
    // TODO: referenced_message
    // TODO: interaction_metadata
    // TODO: thread
    // TODO: components
    // TODO: stickerItems
    // TODO: role_subscription_data
    // TODO: resolved
    // TODO: poll
    // TODO: call
    SBR_OBJECTCREATORHELPERS_DEALLOCATE_MANUAL(message, sizeof(SBR_DiscordMessage), SBR_MEMORY_TYPE_MESSAGE);
}
