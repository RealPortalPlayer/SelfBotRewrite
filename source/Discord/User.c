// Copyright (c) 2024, PortalPlayer <email@portalplayer.xyz>
// Licensed under MIT <https://opensource.org/licenses/MIT>

#include <stdlib.h>
#include <BaconAPI/Debugging/Assert.h>
#include <BaconAPI/Math/Bitwise.h>

#include "Discord/User.h"

#define SBR_DISCORDUSER_GET(key, keyString) json_object* key = json_object_object_get(userData, keyString)

#define SBR_DISCORDUSER_GET_NOT_NULL(key, keyString) \
SBR_DISCORDUSER_GET(key, keyString);                 \
if (key == NULL) {                                   \
    free(user);                                      \
    return NULL;                                     \
}


SBR_DiscordUser* SBR_DiscordUser_Create(json_object* userData) {
    SBR_DiscordUser* user = malloc(sizeof(SBR_DiscordUser));

    BA_ASSERT(user != NULL, "Failed to allocate memory for Discord user\n");
    SBR_DISCORDUSER_GET_NOT_NULL(id, "id");
    SBR_DISCORDUSER_GET_NOT_NULL(username, "username");
    SBR_DISCORDUSER_GET_NOT_NULL(discrimator, "discriminator");
    SBR_DISCORDUSER_GET(globalName, "global_name");
    SBR_DISCORDUSER_GET(avatarHash, "avatar");
    SBR_DISCORDUSER_GET(bot, "bot");
    SBR_DISCORDUSER_GET(system, "system");
    SBR_DISCORDUSER_GET(multiFactorAuthenticationEnabled, "mfa_enabled");
    SBR_DISCORDUSER_GET(bannerHash, "banner");
    SBR_DISCORDUSER_GET(accentColor, "accent_color");
    SBR_DISCORDUSER_GET(locale, "locale");
    SBR_DISCORDUSER_GET(verified, "verified");
    SBR_DISCORDUSER_GET(email, "email");
    SBR_DISCORDUSER_GET(officialFlags, "flags");
    SBR_DISCORDUSER_GET(nitro, "premium_type");
    SBR_DISCORDUSER_GET(publicOfficialFlags, "public_flags");
    SBR_DISCORDUSER_GET(avatarDecoration, "avatar_decoration");

    user->id = SBR_Snowflake_ConvertFromNumber(json_object_get_int(id));
    user->username = json_object_get_string(username);
    user->discriminator = json_object_get_string(discrimator);
    user->globalName = json_object_get_string(globalName);
    user->avatarHash = json_object_get_string(avatarHash);
    user->customFlags = SBR_DISCORDUSER_CUSTOM_FLAG_NULL;

    if (json_object_get_boolean(bot))
        BA_BITWISE_SET_BIT(user->customFlags, SBR_DISCORDUSER_CUSTOM_FLAG_BOT);

    if (json_object_get_boolean(system))
        BA_BITWISE_SET_BIT(user->customFlags, SBR_DISCORDUSER_CUSTOM_FLAG_SYSTEM);

    if (json_object_get_boolean(multiFactorAuthenticationEnabled))
        BA_BITWISE_SET_BIT(user->customFlags, SBR_DISCORDUSER_CUSTOM_FLAG_MULTI_FACTOR_AUTHENTICATION_ENABLED);

    user->bannerHash = json_object_get_string(bannerHash);
    user->accentColor = json_object_get_int(accentColor);
    user->locale = SBR_DISCORDUSER_LOCALE_AMERICAN_ENGLISH; // TODO

    if (json_object_get_boolean(verified))
        BA_BITWISE_SET_BIT(user->customFlags, SBR_DISCORDUSER_CUSTOM_FLAG_EMAIL_VERIFIED);

    user->email = json_object_get_string(email);
    user->officialFlags = json_object_get_int(officialFlags);
    user->nitro = json_object_get_int(nitro);
    user->publicOfficialFlags = json_object_get_int(publicOfficialFlags);
    user->avatarDecoration = json_object_get_string(avatarDecoration);
    return user;
}
