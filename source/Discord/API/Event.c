// Copyright (c) 2024, PortalPlayer <email@portalplayer.xyz>
// Licensed under MIT <https://opensource.org/licenses/MIT>

#include "Discord/API/Event.h"

BA_Boolean SBR_DiscordAPIEvent_IsCodeValid(SBR_DiscordAPIEvent_Codes code) {
    return code < SBR_DISCORDAPIEVENT_CODE_SIZE;
}
