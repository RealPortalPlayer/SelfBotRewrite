// Copyright (c) 2024, PortalPlayer <email@portalplayer.xyz>
// Licensed under MIT <https://opensource.org/licenses/MIT>

#include <BaconAPI/String.h>

#include "Commands/TestCommand.h"
#include "Debugging/Assert.h"

SBR_COMMANDS_CREATE_COMMAND_HEADER(test) {
    char* newMessage = BA_String_Format(BA_String_Copy("Hello, from %s command"), this->name);

    SBR_DiscordMessage_Deallocate(SBR_DiscordChannel_Send(message->channel, newMessage, NULL));
    free(newMessage);
    return NULL;
}
