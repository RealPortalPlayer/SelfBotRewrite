// Copyright (c) 2024, PortalPlayer <email@portalplayer.xyz>
// Licensed under MIT <https://opensource.org/licenses/MIT>

#include <stdlib.h>
#include <BaconAPI/Debugging/Assert.h>

#include "Discord/Application.h"
#include "Discord/ObjectCreatorHelpers.h"

SBR_DiscordApplication* SBR_DiscordApplication_Create(json_object* unparsedJsonData) {
    SBR_OBJECTCREATORHELPERS_HEADER(SBR_DiscordApplication, "Discord application");
    SBR_OBJECTCREATORHELPERS_GET_SNOWFLAKE(id, "", REQUIRED, SAME);
    SBR_OBJECTCREATORHELPERS_GET_STRING(name, "", REQUIRED, SAME);
    SBR_OBJECTCREATORHELPERS_GET_STRING(iconHash, "icon", OPTIONAL, NOT_SAME);
    SBR_OBJECTCREATORHELPERS_SET_BIT_ON_BOOLEAN(botPublic, "bot_public", REQUIRED, NOT_SAME, customFlags, SBR_DISCORDAPPLICATION_CUSTOM_FLAG_BOT_PUBLIC);
    SBR_OBJECTCREATORHELPERS_SET_BIT_ON_BOOLEAN(botRequireCodeGrant, "bot_require_code_grant", REQUIRED, NOT_SAME, customFlags, SBR_DISCORDAPPLICATION_CUSTOM_FLAG_BOT_REQUIRES_GRANT);
    SBR_OBJECTCREATORHELPERS_GET_USER(bot, "", OPTIONAL, SAME);
    SBR_OBJECTCREATORHELPERS_GET_STRING(termsOfServiceUrl, "terms_of_service_url", OPTIONAL, NOT_SAME);
    SBR_OBJECTCREATORHELPERS_GET_STRING(privacyPolicyUrl, "privacy_policy_url", OPTIONAL, NOT_SAME);
    SBR_OBJECTCREATORHELPERS_GET_STRING(verifyKey, "verify_key", REQUIRED, NOT_SAME);
    // TODO: team
    SBR_OBJECTCREATORHELPERS_GET_SNOWFLAKE(guildId, "guild_id", OPTIONAL, NOT_SAME);
    // TODO: guild
    SBR_OBJECTCREATORHELPERS_GET_SNOWFLAKE(primarySkuId, "primary_sku_id", OPTIONAL, NOT_SAME);
    SBR_OBJECTCREATORHELPERS_GET_STRING(storeSlug, "slug", OPTIONAL, NOT_SAME);
    SBR_OBJECTCREATORHELPERS_GET_STRING(richPresenceCoverImage, "cover_image", OPTIONAL, NOT_SAME);
    SBR_OBJECTCREATORHELPERS_GET_INTEGER(officialFlags, "flags", OPTIONAL, NOT_SAME);
    SBR_OBJECTCREATORHELPERS_GET_INTEGER(approximateGuildCount, "approximate_guild_count", OPTIONAL, NOT_SAME);
    SBR_OBJECTCREATORHELPERS_GET_JSON_ARRAY(redirectUris, "redirect_uris", OPTIONAL, NOT_SAME);
    SBR_OBJECTCREATORHELPERS_GET_STRING(roleConnectionsVerificationUrl, "role_connections_verification_url", OPTIONAL, NOT_SAME);
    SBR_OBJECTCREATORHELPERS_GET_JSON_ARRAY(tags, "", OPTIONAL, SAME);
    // TODO: install_params
    SBR_OBJECTCREATORHELPERS_GET_JSON_OBJECT(integrationTypesConfiguration, "integration_types_config", OPTIONAL, NOT_SAME);
    SBR_OBJECTCREATORHELPERS_GET_STRING(customInstallationUrl, "custom_install_url", OPTIONAL, NOT_SAME);
    SBR_OBJECTCREATORHELPERS_FOOTER();
}
