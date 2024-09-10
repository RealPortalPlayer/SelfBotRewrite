// Copyright (c) 2024, PortalPlayer <email@portalplayer.xyz>
// Licensed under MIT <https://opensource.org/licenses/MIT>

#include <BaconAPI/Storage/DynamicDictionary.h>

#include "Commands/HelpCommand.h"
#include "Commands/Category.h"

SBR_COMMANDS_CREATE_COMMAND_HEADER(help) {
    const BA_DynamicDictionary* registeredCategories = SBR_Category_GetAll();
    SBR_EmbedCreator_Embed* embed = SBR_EmbedCreator_Create();

    for (int i = 0; i < registeredCategories->keys.used; i++) {
        const char* name = registeredCategories->keys.internalArray[i];
        const char* description = SBR_Category_GetDescription(name);
        
        SBR_EmbedCreator_AddField(embed, name, description != NULL ? description : "(NULL)", BA_BOOLEAN_TRUE);
    }

    SBR_DiscordMessage_Deallocate(SBR_DiscordChannel_Send(message->channel, "", embed));
    SBR_EmbedCreator_Free(embed);
    return NULL;
}
