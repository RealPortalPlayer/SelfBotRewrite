// Copyright (c) 2024, PortalPlayer <email@portalplayer.xyz>
// Licensed under MIT <https://opensource.org/licenses/MIT>

#include <BaconAPI/Logger.h>
#include <BaconAPI/Math/Bitwise.h>

#include "Discord/Intents.h"
#include "Events.h"
#include "Bot.h"

void SBR_BotSetup_MessageSent(SBR_DiscordMessage* message) {
    // TODO
}

void SBR_BotSetup_Ready(void) {
    BA_LOGGER_INFO("Bot is ready: %s#%s\n", SBR_Bot_Get()->username, SBR_Bot_Get()->discriminator);
}

void SBR_BotSetup_Main(void) {
    SBR_DiscordIntents_Set(SBR_DISCORDINTENT_GUILD_MESSAGES |
                           SBR_DISCORDINTENT_GUILD_MEMBERS |
                           SBR_DISCORDINTENT_DIRECT_MESSAGES |
                           SBR_DISCORDINTENT_GUILD_MODERATION |
                           SBR_DISCORDINTENT_MESSAGE_CONTENT);
    SBR_Events_SetMessageSentAction(&SBR_BotSetup_MessageSent);
    SBR_Events_SetReadyAction(&SBR_BotSetup_Ready);
}
