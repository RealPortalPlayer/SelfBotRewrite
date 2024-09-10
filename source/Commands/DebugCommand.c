// Copyright (c) 2024, PortalPlayer <email@portalplayer.xyz>
// Licensed under MIT <https://opensource.org/licenses/MIT>

#include <stdlib.h>

#include "Commands/DebugCommand.h"
#include "DebugInformation.h"

SBR_COMMANDS_CREATE_COMMAND_HEADER(debug) {
    char* newMessage = SBR_DebugInformation_Get();
    
    SBR_DiscordMessage_Deallocate(SBR_DiscordChannel_Send(message->channel, newMessage, NULL));
    free(newMessage);
    return NULL;
}
