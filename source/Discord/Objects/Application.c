// Copyright (c) 2024, PortalPlayer <email@portalplayer.xyz>
// Licensed under MIT <https://opensource.org/licenses/MIT>

#include <stdlib.h>

#include "Discord/Objects/Application.h"
#include "Discord/Objects/ObjectCreatorHelpers.h"

SBR_DiscordApplication* SBR_DiscordApplication_Create(json_object* unparsedJsonData) {
    SBR_OBJECTCREATORHELPERS_HEADER(SBR_DiscordApplication, SBR_MEMORY_TYPE_APPLICATION, "Discord application");
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
    SBR_OBJECTCREATORHELPERS_GET_JSON_OBJECT(redirectUris, "redirect_uris", OPTIONAL, NOT_SAME);
    SBR_OBJECTCREATORHELPERS_GET_STRING(roleConnectionsVerificationUrl, "role_connections_verification_url", OPTIONAL, NOT_SAME);
    SBR_OBJECTCREATORHELPERS_GET_JSON_OBJECT(tags, "", OPTIONAL, SAME);
    // TODO: install_params
    SBR_OBJECTCREATORHELPERS_GET_JSON_OBJECT(integrationTypesConfiguration, "integration_types_config", OPTIONAL, NOT_SAME);
    SBR_OBJECTCREATORHELPERS_GET_STRING(customInstallationUrl, "custom_install_url", OPTIONAL, NOT_SAME);
    SBR_OBJECTCREATORHELPERS_FOOTER();
}

void SBR_DiscordApplication_Deallocate(SBR_DiscordApplication* application) {
    if (application == NULL)
        return;
    
    SBR_OBJECTCREATORHELPERS_DEALLOCATE_SNOWFLAKE(application->id);
    SBR_OBJECTCREATORHELPERS_DEALLOCATE_USER(application->bot);
    SBR_OBJECTCREATORHELPERS_DEALLOCATE_USER(application->owner);
    SBR_OBJECTCREATORHELPERS_DEALLOCATE_SNOWFLAKE(application->guildId);
    // TODO: guild
    SBR_OBJECTCREATORHELPERS_DEALLOCATE_SNOWFLAKE(application->primarySkuId);
    // TODO: team
    // TODO: redirectUris
    // TODO: tags
    // TODO: install_params
    // TODO: integrationTypesConfiguration
    SBR_OBJECTCREATORHELPERS_DEALLOCATE_MANUAL(application, sizeof(SBR_DiscordApplication), SBR_MEMORY_TYPE_APPLICATION);
}
