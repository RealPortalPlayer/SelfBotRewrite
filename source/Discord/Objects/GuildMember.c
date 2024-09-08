// Copyright (c) 2024, PortalPlayer <email@portalplayer.xyz>
// Licensed under MIT <https://opensource.org/licenses/MIT>

#include "Discord/Objects/GuildMember.h"
#include "Discord/Objects/ObjectCreatorHelpers.h"

SBR_DiscordGuildMember* SBR_DiscordGuildMember_Create(json_object* unparsedJsonData) {
    SBR_OBJECTCREATORHELPERS_HEADER(SBR_DiscordGuildMember, "Discord guild member");
    SBR_OBJECTCREATORHELPERS_GET_USER(user, "", OPTIONAL, SAME);
    SBR_OBJECTCREATORHELPERS_GET_STRING(nick, "", OPTIONAL, SAME);
    SBR_OBJECTCREATORHELPERS_GET_STRING(avatarHash, "avatar_hash", OPTIONAL, NOT_SAME);
    // TODO: roles
    // TODO: joined_at
    // TODO: premium_since
    SBR_OBJECTCREATORHELPERS_SET_BIT_ON_BOOLEAN(deaf, "", REQUIRED, SAME, customFlags, SBR_DISCORDGUILDMEMBER_CUSTOM_FLAG_DEAF);
    SBR_OBJECTCREATORHELPERS_SET_BIT_ON_BOOLEAN(mute, "", REQUIRED, SAME, customFlags, SBR_DISCORDGUILDMEMBER_CUSTOM_FLAG_MUTE);
    SBR_OBJECTCREATORHELPERS_GET_INTEGER(officialFlags, "flags", REQUIRED, NOT_SAME);
    SBR_OBJECTCREATORHELPERS_SET_BIT_ON_BOOLEAN(pending, "", REQUIRED, SAME, customFlags, SBR_DISCORDGUILDMEMBER_CUSTOM_FLAG_PENDING);
    SBR_OBJECTCREATORHELPERS_GET_PERMISSIONS(permissions, "", OPTIONAL, SAME);
    // TODO: communication_disabled_until
    // TODO: avatar_decoration_data
    SBR_OBJECTCREATORHELPERS_FOOTER();
}
