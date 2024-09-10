// Purpose: Registered commands
// Created on: 4/30/24 @ 2:54 PM

// Copyright (c) 2024, PortalPlayer <email@portalplayer.xyz>
// Licensed under MIT <https://opensource.org/licenses/MIT>

#pragma once

#include "Discord/Objects/Message.h"
#include "Command.h"

void SBR_Commands_Register(void);

#define SBR_COMMANDS_CREATE_COMMAND_HEADER(name) const char* SBR_Commands_ ## name(const SBR_Command* this, SBR_DiscordMessage* message)
