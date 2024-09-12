// Copyright (c) 2024, PortalPlayer <email@portalplayer.xyz>
// Licensed under MIT <https://opensource.org/licenses/MIT>

#include <stdlib.h>

#include "Discord/Objects/User.h"
#include "Discord/Objects/ObjectCreatorHelpers.h"
#include "Discord/API/Events.h"

SBR_DiscordUser* SBR_DiscordUser_Create(json_object* unparsedJsonData) {
    SBR_OBJECTCREATORHELPERS_HEADER(SBR_DiscordUser, SBR_MEMORY_TYPE_USER, "Discord user");
    SBR_OBJECTCREATORHELPERS_GET_SNOWFLAKE(id, "", REQUIRED, SAME);
    SBR_OBJECTCREATORHELPERS_GET_STRING(username, "", REQUIRED, SAME);
    SBR_OBJECTCREATORHELPERS_GET_STRING(discriminator, "", REQUIRED, SAME);
    SBR_OBJECTCREATORHELPERS_GET_STRING(globalName, "global_name", UNREQUIRED, NOT_SAME);
    SBR_OBJECTCREATORHELPERS_GET_STRING(avatarHash, "avatar", UNREQUIRED, NOT_SAME);
    SBR_OBJECTCREATORHELPERS_SET_BIT_ON_BOOLEAN(bot, "", UNREQUIRED, SAME, customFlags, SBR_DISCORDUSER_CUSTOM_FLAG_BOT);
    SBR_OBJECTCREATORHELPERS_SET_BIT_ON_BOOLEAN(system, "", UNREQUIRED, SAME, customFlags, SBR_DISCORDUSER_CUSTOM_FLAG_SYSTEM);
    SBR_OBJECTCREATORHELPERS_SET_BIT_ON_BOOLEAN(multiFactorAuthenticationEnabled, "mfa_enabled", UNREQUIRED, NOT_SAME, customFlags, SBR_DISCORDUSER_CUSTOM_FLAG_MULTI_FACTOR_AUTHENTICATION_ENABLED);
    SBR_OBJECTCREATORHELPERS_GET_STRING(bannerHash, "banner", UNREQUIRED, NOT_SAME);
    SBR_OBJECTCREATORHELPERS_GET_INTEGER(accentColor, "accent_color", UNREQUIRED, NOT_SAME);
    SBR_OBJECTCREATORHELPERS_GET_LOCALE(locale, "", UNREQUIRED, SAME);
    SBR_OBJECTCREATORHELPERS_SET_BIT_ON_BOOLEAN(verified, "", UNREQUIRED, SAME, customFlags, SBR_DISCORDUSER_CUSTOM_FLAG_EMAIL_VERIFIED);
    SBR_OBJECTCREATORHELPERS_GET_STRING(email, "", UNREQUIRED, SAME);
    SBR_OBJECTCREATORHELPERS_GET_INTEGER(officialFlags, "flags", UNREQUIRED, NOT_SAME);
    SBR_OBJECTCREATORHELPERS_GET_INTEGER(nitro, "premium_type", UNREQUIRED, NOT_SAME);
    SBR_OBJECTCREATORHELPERS_GET_INTEGER(publicOfficialFlags, "public_flags", UNREQUIRED, NOT_SAME);
    SBR_OBJECTCREATORHELPERS_GET_STRING(avatarDecoration, "avatar_decoration", UNREQUIRED, NOT_SAME);
    SBR_OBJECTCREATORHELPERS_FOOTER();
}

const char* SBR_DiscordUser_NitroTypeToString(SBR_DiscordUser_NitroTypes nitroType) {
    switch (nitroType) {
        case SBR_DISCORDUSER_NITRO_TYPE_NONE: return "None";
        case SBR_DISCORDUSER_NITRO_TYPE_NITRO_CLASSIC: return "Nitro Classic";
        case SBR_DISCORDUSER_NITRO_TYPE_NITRO: return "Nitro";
        case SBR_DISCORDUSER_NITRO_TYPE_NITRO_BASIC: return "Nitro Basic";
        default:
            BA_LOGGER_WARN("Invalid Nitro type: %i\n", nitroType);
            return "Unknown";
    }
}

SBR_DiscordUser* SBR_DiscordUser_Get(const SBR_Snowflake* id) {
    return SBR_DiscordAPIEvents_GetUser(id);
}

void SBR_DiscordUser_Deallocate(SBR_DiscordUser* user) {
    if (user == NULL)
        return;
    
    SBR_OBJECTCREATORHELPERS_DEALLOCATE_SNOWFLAKE(user->id);
    SBR_OBJECTCREATORHELPERS_DEALLOCATE_MANUAL(user, sizeof(SBR_DiscordUser), SBR_MEMORY_TYPE_USER);
}
