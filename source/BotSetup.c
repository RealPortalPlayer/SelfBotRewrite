// Copyright (c) 2024, PortalPlayer <email@portalplayer.xyz>
// Licensed under MIT <https://opensource.org/licenses/MIT>

#include <string.h>
#include <BaconAPI/Logger.h>
#include <BaconAPI/String.h>
#include <BaconAPI/Math/Bitwise.h>
#include <BaconAPI/String.h>

#include "Discord/Intents.h"
#include "Events.h"
#include "Bot.h"
#include "Commands/Commands.h"
#include "Commands/Command.h"
#include "Prefix.h"
#include "Commands/Categories.h"
#include "SupportChannels.h"
#include "DebugInformation.h"

void SBR_BotSetup_MessageSent(SBR_DiscordMessage* message) {
    if (message->content == NULL ||
        BA_BITWISE_IS_BIT_SET(message->author->customFlags, SBR_DISCORDUSER_CUSTOM_FLAG_BOT) ||
        !BA_String_StartsWith(message->content, SBR_Prefix_Get(), BA_BOOLEAN_TRUE))
        return;

    size_t prefixLength = strlen(SBR_Prefix_Get());
    size_t messageLength = strlen(message->content) - prefixLength + 1;
    char* prefixlessMessage = malloc(sizeof(char) * messageLength);

    memcpy(prefixlessMessage, message->content + prefixLength, messageLength);

    prefixlessMessage[messageLength] = '\0';

    BA_DynamicArray* arguments = BA_String_SplitCharacter(prefixlessMessage, ' ');
    char* name = arguments->internalArray[0];
    const SBR_Command* command = SBR_Command_Get(name, SBR_COMMAND_TYPE_CLASSIC);

    BA_DynamicArray_RemoveFirstElement(arguments);
    
    if (command == NULL)
        goto destroy;
    
    {
        const char* results = command->Action(command, message);
        SBR_EmbedCreator_Embed* embed = SBR_EmbedCreator_Create();
        char* parsedId = BA_String_Copy("%lu");

        SBR_EmbedCreator_AddField(embed, "Success", results == NULL ? "true" : "false", BA_BOOLEAN_TRUE);
        SBR_EmbedCreator_AddField(embed, "Command", name, BA_BOOLEAN_TRUE);
        SBR_EmbedCreator_AddField(embed, "Arguments", "None", BA_BOOLEAN_TRUE); // TODO
        SBR_EmbedCreator_AddField(embed, "Message", message->content, BA_BOOLEAN_TRUE);
        SBR_EmbedCreator_AddField(embed, "ID", BA_String_Format(&parsedId, SBR_Snowflake_ConvertToNumber(message->author->id)), BA_BOOLEAN_TRUE);

        if (message->channel->type == SBR_DISCORDCHANNEL_TYPE_GUILD_TEXT && !message->channel->guild->unavailable) {
            free(parsedId);

            parsedId = BA_String_Copy("%lu");

            SBR_EmbedCreator_AddField(embed, "Guild ID", BA_String_Format(&parsedId, SBR_Snowflake_ConvertToNumber(message->channel->guild->id)), BA_BOOLEAN_TRUE);
            free(parsedId);

            parsedId = BA_String_Copy("%lu");

            SBR_EmbedCreator_AddField(embed, "Guild Owner ID", BA_String_Format(&parsedId, SBR_Snowflake_ConvertToNumber(message->channel->guild->ownerId)), BA_BOOLEAN_TRUE);
        }

        if (results != NULL)
            SBR_EmbedCreator_AddField(embed, "Reason", results, BA_BOOLEAN_TRUE);

        SBR_DiscordMessage_Deallocate(SBR_SupportChannels_SendLogsMessage("", embed));
        free(parsedId);
        SBR_EmbedCreator_Free(embed);
    }
    
    destroy:
    free(prefixlessMessage);
    free(name);
    
    for (int i = 0; i < arguments->used; i++)
        free(arguments->internalArray[i]);

    free(arguments->internalArray);
    free(arguments);
}

void SBR_BotSetup_Ready(void) {
    BA_LOGGER_INFO("Bot is ready: %s#%s\n", SBR_Bot_Get()->username, SBR_Bot_Get()->discriminator);
    SBR_Commands_Register();
    SBR_Categories_Register();

    char* message = BA_String_Copy("Bot successfully started%s\n%s");
    char* debugInformation = SBR_DebugInformation_Get();

#if DEBUG
#   define SBR_BOTSETUP_ADDITIONAL_MESSAGE " (DEBUG BUILD)"
#else
#   define SBR_BOTSETUP_ADDITIONAL_MESSAGE ""
#endif
    
    SBR_DiscordMessage_Deallocate(SBR_SupportChannels_SendLogsMessage(BA_String_Format(&message, SBR_BOTSETUP_ADDITIONAL_MESSAGE, debugInformation), NULL));
    free(debugInformation);
    free(message);
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
