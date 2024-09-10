// Purpose: Senders for support channels
// Created on: 9/8/24 @ 2:10 PM


// Copyright (c) 2024, PortalPlayer <email@portalplayer.xyz>
// Licensed under MIT <https://opensource.org/licenses/MIT>

#pragma once

#include "Discord/Objects/Message.h"
#include "Discord/EmbedCreator.h"

#define SBR_SUPPORTCHANNELS_CREATE_FUNCTION_HEADER(type) SBR_DiscordMessage* SBR_SupportChannels_Send ## type ## Message(const char* content, SBR_EmbedCreator_Embed* embed)

SBR_SUPPORTCHANNELS_CREATE_FUNCTION_HEADER(Logs);
SBR_SUPPORTCHANNELS_CREATE_FUNCTION_HEADER(Bugs);
SBR_SUPPORTCHANNELS_CREATE_FUNCTION_HEADER(Suggestions);

void SBR_SupportChannels_Deallocate(void);
