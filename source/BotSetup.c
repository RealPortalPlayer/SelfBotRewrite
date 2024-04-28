// Copyright (c) 2024, PortalPlayer <email@portalplayer.xyz>
// Licensed under MIT <https://opensource.org/licenses/MIT>

#include "Discord/Intents.h"

void SBR_BotSetup_Main(void) {
    SBR_DiscordIntents_Set(SBR_DISCORDINTENT_GUILD_MESSAGES |
                           SBR_DISCORDINTENT_GUILD_MEMBERS |
                           SBR_DISCORDINTENT_DIRECT_MESSAGES |
                           SBR_DISCORDINTENT_GUILD_MODERATION |
                           SBR_DISCORDINTENT_MESSAGE_CONTENT);
}
