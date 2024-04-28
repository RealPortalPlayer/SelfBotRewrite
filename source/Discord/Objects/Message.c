// Copyright (c) 2024, PortalPlayer <email@portalplayer.xyz>
// Licensed under MIT <https://opensource.org/licenses/MIT>

#include "Discord/Objects/Message.h"
#include "Discord/Objects/ObjectCreatorHelpers.h"

SBR_DiscordMessage* SBR_DiscordMessage_Create(const json_object* unparsedJsonData) {
    SBR_OBJECTCREATORHELPERS_HEADER(SBR_DiscordMessage, "Discord message");
    SBR_OBJECTCREATORHELPERS_GET_SNOWFLAKE(id, "", REQUIRED, SAME);
    // TODO: channel
    SBR_OBJECTCREATORHELPERS_GET_SNOWFLAKE(channelId, "channel_id", REQUIRED, NOT_SAME);
    SBR_OBJECTCREATORHELPERS_GET_USER(author, "", REQUIRED, SAME);
    SBR_OBJECTCREATORHELPERS_GET_STRING(content, "", REQUIRED, SAME);
    // TODO: timestamp
    // TODO: edited_timestamp
    SBR_OBJECTCREATORHELPERS_SET_BIT_ON_BOOLEAN(textToSpeech, "tts", REQUIRED, NOT_SAME, customFlags, SBR_DISCORDMESSAGE_CUSTOM_FLAG_TEXT_TO_SPEECH);
    SBR_OBJECTCREATORHELPERS_SET_BIT_ON_BOOLEAN(mentionEveryone, "mention_everyone", REQUIRED, NOT_SAME, customFlags, SBR_DISCORDMESSAGE_CUSTOM_FLAG_MENTIONS_EVERYONE);
    // TODO: mentions
    // TODO: mentions_roles
    // TODO: mentions_channels
    // TODO: attachments
    // TODO: embeds
    // TODO: reactions
    SBR_OBJECTCREATORHELPERS_GET_STRING(nonce, "", OPTIONAL, SAME);
    SBR_OBJECTCREATORHELPERS_SET_BIT_ON_BOOLEAN(pinned, "", REQUIRED, SAME, customFlags, SBR_DISCORDMESSAGE_CUSTOM_FLAG_PINNED);
    SBR_OBJECTCREATORHELPERS_GET_SNOWFLAKE(webhookId, "webhook_id", OPTIONAL, NOT_SAME);
    SBR_OBJECTCREATORHELPERS_GET_INTEGER(type, "", REQUIRED, SAME);
    // TODO: activity
    // TODO: application
    SBR_OBJECTCREATORHELPERS_GET_SNOWFLAKE(applicationId, "application_id", OPTIONAL, NOT_SAME);
    // TODO: message_reference
    SBR_OBJECTCREATORHELPERS_GET_INTEGER(officialFlags, "flags", OPTIONAL, NOT_SAME);
    // TODO: referenced_message
    // TODO: interaction_metadata
    // TODO: thread
    // TODO: components
    // TODO: sticker_items
    SBR_OBJECTCREATORHELPERS_GET_INTEGER(position, "", OPTIONAL, SAME);
    // TODO: role_subscription_date
    // TODO: resolved
    // TODO: poll
    SBR_OBJECTCREATORHELPERS_FOOTER();
}
