// Copyright (c) 2024, PortalPlayer <email@portalplayer.xyz>
// Licensed under MIT <https://opensource.org/licenses/MIT>

#include <BaconAPI/Math/Bitwise.h>

#include "Discord/Intents.h"

static SBR_DiscordIntents sbrDiscordIntents;

SBR_DiscordIntents SBR_DiscordIntents_Get(void) {
    return sbrDiscordIntents;
}

void SBR_DiscordIntents_Set(SBR_DiscordIntents intents) {
    sbrDiscordIntents = intents;
}

void SBR_DiscordIntents_Add(SBR_DiscordIntents intents) {
    BA_BITWISE_SET_BIT(sbrDiscordIntents, intents);
}
