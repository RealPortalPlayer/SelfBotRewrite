// Copyright (c) 2024, PortalPlayer <email@portalplayer.xyz>
// Licensed under MIT <https://opensource.org/licenses/MIT>

#include <stdlib.h>

#include "Bot.h"

static SBR_DiscordUser* sbrBotUser = NULL;

const SBR_DiscordUser* SBR_Bot_Get(void) {
    return sbrBotUser;
}

void SBR_Bot_Set(SBR_DiscordUser* user) {
    if (sbrBotUser != NULL)
        free(sbrBotUser);

    sbrBotUser = user;
}
