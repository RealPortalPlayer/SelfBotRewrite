// Copyright (c) 2024, PortalPlayer <email@portalplayer.xyz>
// Licensed under MIT <https://opensource.org/licenses/MIT>

#include <string.h>
#include <BaconAPI/Logger.h>
#include <BaconAPI/String.h>
#include <BaconAPI/Math/Bitwise.h>

#include "Discord/Intents.h"
#include "Events.h"
#include "Bot.h"
#include "Commands/Commands.h"
#include "Commands/Command.h"
#include "Prefix.h"
#include "Commands/Categories.h"

void SBR_BotSetup_MessageSent(SBR_DiscordMessage* message) {
    if (message->content == NULL ||
        BA_BITWISE_IS_BIT_SET(message->author->customFlags, SBR_DISCORDUSER_CUSTOM_FLAG_BOT) ||
        !BA_String_StartsWith(message->content, SBR_Prefix_Get(), BA_BOOLEAN_TRUE))
        return;

    size_t prefixLength = strlen(SBR_Prefix_Get());
    size_t messageLength = strlen(message->content) - prefixLength + 1;
    char prefixlessMessage[messageLength];

    memcpy(prefixlessMessage, message->content + prefixLength, messageLength);

    prefixlessMessage[messageLength] = '\0';

    BA_DynamicArray* arguments = BA_String_SplitCharacter(prefixlessMessage, ' ');
    const SBR_Command* command = SBR_Command_Get(arguments->internalArray[0], SBR_COMMAND_TYPE_CLASSIC);

    if (command == NULL)
        goto destroy;

    command->Action(command, message);
    destroy:
    for (int i = 0; i < arguments->used; i++)
        free(arguments->internalArray[i]);

    free(arguments->internalArray);
    free(arguments);
    free(message->author);
    free(message->channel);
    free(message);
}

void SBR_BotSetup_Ready(void) {
    BA_LOGGER_INFO("Bot is ready: %s#%s\n", SBR_Bot_Get()->username, SBR_Bot_Get()->discriminator);
    SBR_Commands_Register();
    SBR_Categories_Register();
}

void SBR_BotSetup_Main(void) {
    SBR_DiscordIntents_Set(SBR_DISCORDINTENT_GUILD_MESSAGES |
                           SBR_DISCORDINTENT_GUILD_MEMBERS |
                           SBR_DISCORDINTENT_DIRECT_MESSAGES |
                           SBR_DISCORDINTENT_GUILD_MODERATION |
                           SBR_DISCORDINTENT_MESSAGE_CONTENT);
    SBR_Events_SetMessageSentAction(&SBR_BotSetup_MessageSent);
    SBR_Events_SetReadyAction(&SBR_BotSetup_Ready);
}
