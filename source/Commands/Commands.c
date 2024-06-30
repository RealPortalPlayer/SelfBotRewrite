// Copyright (c) 2024, PortalPlayer <email@portalplayer.xyz>
// Licensed under MIT <https://opensource.org/licenses/MIT>

#include <BaconAPI/Logger.h>
#include <BaconAPI/String.h>
#include <BaconAPI/Math/Bitwise.h>

#include "Commands/Commands.h"
#include "Commands/Command.h"

#define SBR_COMMANDS_CREATE_COMMAND_HEADER(name) void SBR_Commands_ ## name(const SBR_Command* this, SBR_DiscordMessage* message)
#define SBR_COMMANDS_REGISTER(name, description, type) SBR_Command_Register(#name, description, type, (SBR_Command_Action) &SBR_Commands_ ## name)

SBR_COMMANDS_CREATE_COMMAND_HEADER(test);
SBR_COMMANDS_CREATE_COMMAND_HEADER(help);

void SBR_Commands_Register(void) {
    BA_LOGGER_INFO("Registering all commands\n");
    SBR_COMMANDS_REGISTER(test, "Testing command", SBR_COMMAND_TYPE_CLASSIC);
    SBR_COMMANDS_REGISTER(help, "Information about each command", SBR_COMMAND_TYPE_CLASSIC);
}

SBR_COMMANDS_CREATE_COMMAND_HEADER(test) {
    char* newMessage = BA_String_Copy("Hello, from %s command");
    
    SBR_DiscordChannel_Send(message->channel, BA_String_Format(&newMessage, this->name), NULL);
    free(newMessage);
}

SBR_COMMANDS_CREATE_COMMAND_HEADER(help) {
    const BA_DynamicArray* registeredCommands = SBR_Command_GetAll();
    SBR_EmbedCreator_Embed* embed = SBR_EmbedCreator_Create();

    for (int i = 0; i < registeredCommands->used; i++) {
        SBR_Command* command = BA_DYNAMICARRAY_GET_ELEMENT_POINTER(SBR_Command, registeredCommands, i);

        if (!BA_BITWISE_IS_BIT_SET(command->type, SBR_COMMAND_TYPE_CLASSIC))
            continue;

        SBR_EmbedCreator_AddField(embed, command->name, command->description, BA_BOOLEAN_TRUE);
    }

    SBR_DiscordChannel_Send(message->channel, "", embed);
    SBR_EmbedCreator_Free(embed);
}
