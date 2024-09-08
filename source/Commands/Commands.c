// Copyright (c) 2024, PortalPlayer <email@portalplayer.xyz>
// Licensed under MIT <https://opensource.org/licenses/MIT>

#include <BaconAPI/Logger.h>
#include <BaconAPI/String.h>
#include <BaconAPI/Math/Bitwise.h>
#include <BaconAPI/Storage/DynamicDictionary.h>

#include "Commands/Commands.h"
#include "Commands/Command.h"
#include "Commands/Category.h"

#define SBR_COMMANDS_CREATE_COMMAND_HEADER(name) void SBR_Commands_ ## name(const SBR_Command* this, SBR_DiscordMessage* message)
#define SBR_COMMANDS_REGISTER(name, description, category, type) SBR_Command_Register(#name, description, category, type, (SBR_Command_Action) &SBR_Commands_ ## name)

SBR_COMMANDS_CREATE_COMMAND_HEADER(test);
SBR_COMMANDS_CREATE_COMMAND_HEADER(help);

void SBR_Commands_Register(void) {
    BA_LOGGER_INFO("Registering all commands\n");
    SBR_COMMANDS_REGISTER(test, "Testing command", "misc", SBR_COMMAND_TYPE_CLASSIC);
    SBR_COMMANDS_REGISTER(help, "Information about each command", "misc", SBR_COMMAND_TYPE_CLASSIC);
}

SBR_COMMANDS_CREATE_COMMAND_HEADER(test) {
    char* newMessage = BA_String_Copy("Hello, from %s command");
    
    SBR_DiscordChannel_Send(message->channel, BA_String_Format(&newMessage, this->name), NULL);
    free(newMessage);
}

SBR_COMMANDS_CREATE_COMMAND_HEADER(help) {
    const BA_DynamicDictionary* registeredCategories = SBR_Category_GetAll();
    SBR_EmbedCreator_Embed* embed = SBR_EmbedCreator_Create();

    for (int i = 0; i < registeredCategories->keys.used; i++) {
        const char* name = registeredCategories->keys.internalArray[i];
        const char* description = SBR_Category_GetDescription(name);
        
        SBR_EmbedCreator_AddField(embed, name, description != NULL ? description : "(NULL)", BA_BOOLEAN_TRUE);
    }

    SBR_DiscordChannel_Send(message->channel, "", embed);
    SBR_EmbedCreator_Free(embed);
}
