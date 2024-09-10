// Copyright (c) 2024, PortalPlayer <email@portalplayer.xyz>
// Licensed under MIT <https://opensource.org/licenses/MIT>

#include "Discord/Objects/Emoji.h"
#include "Discord/Objects/ObjectCreatorHelpers.h"

SBR_DiscordEmoji* SBR_DiscordEmoji_Create(json_object* unparsedJsonData) {
    SBR_OBJECTCREATORHELPERS_HEADER(SBR_DiscordEmoji, SBR_MEMORY_TYPE_EMOJI, "Discord emoji");
    SBR_OBJECTCREATORHELPERS_GET_SNOWFLAKE(id, "", OPTIONAL, SAME);
    SBR_OBJECTCREATORHELPERS_GET_STRING(name, "", OPTIONAL, SAME);
    // TODO: roles
    SBR_OBJECTCREATORHELPERS_GET_USER(user, "", OPTIONAL, SAME);
    SBR_OBJECTCREATORHELPERS_SET_BIT_ON_BOOLEAN(requireColons, "require_colons", OPTIONAL, NOT_SAME, customFlags, SBR_DISCORDEMOJI_CUSTOM_FLAG_REQUIRE_COLONS);
    SBR_OBJECTCREATORHELPERS_SET_BIT_ON_BOOLEAN(managed, "", OPTIONAL, SAME, customFlags, SBR_DISCORDEMOJI_CUSTOM_FLAG_MANAGED);
    SBR_OBJECTCREATORHELPERS_SET_BIT_ON_BOOLEAN(animated, "", OPTIONAL, SAME, customFlags, SBR_DISCORDEMOJI_CUSTOM_FLAG_ANIMATED);
    SBR_OBJECTCREATORHELPERS_SET_BIT_ON_BOOLEAN(available, "", OPTIONAL, SAME, customFlags, SBR_DISCORDEMOJI_CUSTOM_FLAG_AVAILABLE);
    SBR_OBJECTCREATORHELPERS_FOOTER();
}

void SBR_DiscordEmoji_Deallocate(SBR_DiscordEmoji* emoji) {
    if (emoji == NULL)
        return;
    
    SBR_OBJECTCREATORHELPERS_DEALLOCATE_SNOWFLAKE(emoji->id);
    SBR_OBJECTCREATORHELPERS_DEALLOCATE_USER(emoji->user);
    SBR_OBJECTCREATORHELPERS_DEALLOCATE_MANUAL(emoji, sizeof(SBR_DiscordEmoji), SBR_MEMORY_TYPE_EMOJI);
}
