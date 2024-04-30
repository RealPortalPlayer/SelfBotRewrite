// Copyright (c) 2024, PortalPlayer <email@portalplayer.xyz>
// Licensed under MIT <https://opensource.org/licenses/MIT>

#include <BaconAPI/Logger.h>

#include "Commands/Commands.h"

#include <MainLoop.h>
#include <BaconAPI/String.h>

#include "Commands/Command.h"

#define SBR_COMMANDS_CREATE_COMMAND_HEADER(name) void SBR_Commands_ ## name(const SBR_Command* this, SBR_DiscordMessage* message)
#define SBR_COMMANDS_REGISTER(name, description, type) SBR_Command_Register(#name, description, type, (SBR_Command_Action) &SBR_Commands_ ## name)

SBR_COMMANDS_CREATE_COMMAND_HEADER(test);

void SBR_Commands_Register(void) {
    BA_LOGGER_INFO("Registering all commands\n");
    SBR_COMMANDS_REGISTER(test, "Testing command", SBR_COMMAND_TYPE_CLASSIC);
}

SBR_COMMANDS_CREATE_COMMAND_HEADER(test) {
    char* newMessage = BA_String_Copy("Hello, from %s command");
    
    SBR_DiscordChannel_Send(message->channel, BA_String_Format(&newMessage, this->name), NULL);
    free(newMessage);
}
