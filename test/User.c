// Copyright (c) 2024, PortalPlayer <email@portalplayer.xyz>
// Licensed under MIT <https://opensource.org/licenses/MIT>

#include <json_object.h>
#include <string.h>
#include <BaconAPI/ArgumentHandler.h>
#include <BaconAPI/Logger.h>
#include <BaconAPI/Debugging/Assert.h>
#include <BaconAPI/Internal/Boolean.h>
#include <Discord/Objects/User.h>

#define SET(key, value) json_object_object_add(fake, key, value)
#define VALUE_OR_NULL(key) key != NULL ? key : "(NULL)"
#define ASSERT(test) BA_ASSERT(test, "Unexpected value\n")

int main(int argc, char** argv) {
    BA_ArgumentHandler_Initialize(argc, argv);
    
    json_object* fake = json_object_new_object();

    SET("id", json_object_new_uint64(353541155729833985));
    SET("username", json_object_new_string("baconflavorhair"));
    SET("discriminator", json_object_new_string("0000"));
    SET("global_name", json_object_new_string("BaconFlavorHair"));
    SET("avatar", json_object_new_string("06fdf703d53cfec5da5f503eaad51872"));
    SET("mfa_enabled", json_object_new_boolean(BA_BOOLEAN_TRUE));
    SET("verified", json_object_new_boolean(BA_BOOLEAN_TRUE));
    SET("flags", json_object_new_int(SBR_DISCORDUSER_OFFICIAL_FLAG_HYPESQUAD_BRAVERY_HOUSE | SBR_DISCORDUSER_OFFICIAL_FLAG_EARY_NITRO_SUPPORTER));
    SET("public_flags", json_object_new_int(SBR_DISCORDUSER_OFFICIAL_FLAG_HYPESQUAD_BRAVERY_HOUSE | SBR_DISCORDUSER_OFFICIAL_FLAG_EARY_NITRO_SUPPORTER));

    SBR_DiscordUser* user = SBR_DiscordUser_Create(fake);

    BA_LOGGER_INFO("User:\n"
                   "ID: (%lu, %i, %i, %i, %lu)\n"
                   "Username: %s\n"
                   "Discriminator: %s\n"
                   "Global Name: %s\n"
                   "Avatar Hash: %s\n"
                   "Custom Flags: %i\n"
                   "Banner Hash: %s\n"
                   "Accent Color: %i\n"
                   "Email: %s\n"
                   "Official Flags: %i\n"
                   "Nitro: %i\n"
                   "Public Official Flags: %i\n"
                   "Avatar Decoration: %s\n",
                   user->id->timestamp, user->id->workerId, user->id->processId, user->id->increment, user->id->original,
                   user->username,
                   user->discriminator,
                   VALUE_OR_NULL(user->globalName),
                   VALUE_OR_NULL(user->avatarHash),
                   user->customFlags,
                   VALUE_OR_NULL(user->bannerHash),
                   user->accentColor,
                   VALUE_OR_NULL(user->email),
                   user->officialFlags,
                   user->nitro,
                   user->publicOfficialFlags,
                   VALUE_OR_NULL(user->avatarDecoration));

    ASSERT(user->id->timestamp == 1504361180003UL);
    ASSERT(user->id->workerId == 1);
    ASSERT(user->id->processId == 0);
    ASSERT(user->id->increment == 1);
    ASSERT(user->id->original == 353541155729833985);
    ASSERT(strcmp(user->username, "baconflavorhair") == 0);
    ASSERT(strcmp(user->discriminator, "0000") == 0);
    ASSERT(strcmp(user->globalName, "BaconFlavorHair") == 0);
    ASSERT(strcmp(user->avatarHash, "06fdf703d53cfec5da5f503eaad51872") == 0);
    ASSERT(user->customFlags == SBR_DISCORDUSER_CUSTOM_FLAG_MULTI_FACTOR_AUTHENTICATION_ENABLED | SBR_DISCORDUSER_CUSTOM_FLAG_EMAIL_VERIFIED);
    ASSERT(user->bannerHash == NULL);
    ASSERT(user->accentColor == 0);
    ASSERT(user->email == NULL);
    ASSERT(user->officialFlags == SBR_DISCORDUSER_OFFICIAL_FLAG_HYPESQUAD_BRAVERY_HOUSE | SBR_DISCORDUSER_OFFICIAL_FLAG_EARY_NITRO_SUPPORTER);
    ASSERT(user->nitro == SBR_DISCORDUSER_NITRO_TYPE_NONE);
    ASSERT(user->publicOfficialFlags == SBR_DISCORDUSER_OFFICIAL_FLAG_HYPESQUAD_BRAVERY_HOUSE | SBR_DISCORDUSER_OFFICIAL_FLAG_EARY_NITRO_SUPPORTER);
    ASSERT(user->avatarDecoration == NULL);
    free(user);
}
