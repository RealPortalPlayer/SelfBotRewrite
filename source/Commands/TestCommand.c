// Copyright (c) 2024, PortalPlayer <email@portalplayer.xyz>
// Licensed under MIT <https://opensource.org/licenses/MIT>

#include <BaconAPI/String.h>

#include "Commands/TestCommand.h"
#include "Debugging/Assert.h"

SBR_COMMANDS_CREATE_COMMAND_HEADER(test) {
    char* newMessage = BA_String_Copy("Hello, from %s command");

    SBR_DiscordMessage_Deallocate(SBR_DiscordChannel_Send(message->channel, BA_String_Format(&newMessage, this->name), NULL));
    free(newMessage);
    return NULL;
}
