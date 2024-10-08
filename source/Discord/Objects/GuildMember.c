// Copyright (c) 2024, PortalPlayer <email@portalplayer.xyz>
// Licensed under MIT <https://opensource.org/licenses/MIT>

#include "Discord/Objects/GuildMember.h"
#include "Discord/Objects/ObjectCreatorHelpers.h"

SBR_DiscordGuildMember* SBR_DiscordGuildMember_Create(json_object* unparsedJsonData) {
    SBR_OBJECTCREATORHELPERS_HEADER(SBR_DiscordGuildMember, SBR_MEMORY_TYPE_GUILD_MEMBER, "Discord guild member");
    SBR_OBJECTCREATORHELPERS_GET_USER(user, "", UNREQUIRED, SAME);
    SBR_OBJECTCREATORHELPERS_GET_STRING(nick, "", UNREQUIRED, SAME);
    SBR_OBJECTCREATORHELPERS_GET_STRING(avatarHash, "avatar_hash", UNREQUIRED, NOT_SAME);
    // TODO: roles
    SBR_OBJECTCREATORHELPERS_GET_TIME(joinedAt, "joined_at", REQUIRED, NOT_SAME);
    SBR_OBJECTCREATORHELPERS_GET_TIME(premiumSince, "premium_since", UNREQUIRED, NOT_SAME);
    SBR_OBJECTCREATORHELPERS_SET_BIT_ON_BOOLEAN(deaf, "", REQUIRED, SAME, customFlags, SBR_DISCORDGUILDMEMBER_CUSTOM_FLAG_DEAF);
    SBR_OBJECTCREATORHELPERS_SET_BIT_ON_BOOLEAN(mute, "", REQUIRED, SAME, customFlags, SBR_DISCORDGUILDMEMBER_CUSTOM_FLAG_MUTE);
    SBR_OBJECTCREATORHELPERS_GET_INTEGER(officialFlags, "flags", REQUIRED, NOT_SAME);
    SBR_OBJECTCREATORHELPERS_SET_BIT_ON_BOOLEAN(pending, "", REQUIRED, SAME, customFlags, SBR_DISCORDGUILDMEMBER_CUSTOM_FLAG_PENDING);
    SBR_OBJECTCREATORHELPERS_GET_PERMISSIONS(permissions, "", UNREQUIRED, SAME);
    SBR_OBJECTCREATORHELPERS_GET_TIME(communicationDisabledUntil, "communication_disabled_until", UNREQUIRED, NOT_SAME);
    // TODO: avatar_decoration_data
    SBR_OBJECTCREATORHELPERS_FOOTER();
}

void SBR_DiscordGuildMember_Deallocate(SBR_DiscordGuildMember* guildMember) {
    if (guildMember == NULL)
        return;
    
    SBR_OBJECTCREATORHELPERS_DEALLOCATE_USER(guildMember->user);
    // TODO: roles
    SBR_OBJECTCREATORHELPERS_DEALLOCATE_TIME(guildMember->joinedAt);
    SBR_OBJECTCREATORHELPERS_DEALLOCATE_TIME(guildMember->premiumSince);
    SBR_OBJECTCREATORHELPERS_DEALLOCATE_TIME(guildMember->communicationDisabledUntil);
    // TODO: avatar_decoration_data
    SBR_OBJECTCREATORHELPERS_DEALLOCATE_MANUAL(guildMember, sizeof(SBR_DiscordGuildMember), SBR_MEMORY_TYPE_GUILD_MEMBER);
}
