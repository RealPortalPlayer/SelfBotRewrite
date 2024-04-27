// Copyright (c) 2024, PortalPlayer <email@portalplayer.xyz>
// Licensed under MIT <https://opensource.org/licenses/MIT>

#include "Discord/Objects/Channel.h"
#include "Discord/API/Events.h"

void SBR_DiscordChannel_Send(const SBR_Snowflake* id, const char* content) {
    SBR_DiscordAPIEvents_SendMessage(id, content);
    // TODO: Return created channel
}
