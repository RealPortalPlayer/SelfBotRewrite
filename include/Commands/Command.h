// Purpose: Basic structure of any command
// Created on: 4/30/24 @ 2:13 PM

// Copyright (c) 2024, PortalPlayer <email@portalplayer.xyz>
// Licensed under MIT <https://opensource.org/licenses/MIT>

#pragma once

#include "../Discord/Objects/Message.h"

// TODO: Arguments

struct SBR_Command;

/**
 * @returns Null if no error occurred
 */
typedef const char* (*SBR_Command_Action)(const struct SBR_Command* this, SBR_DiscordMessage* message);

typedef enum {
    SBR_COMMAND_TYPE_TERMINAL = 1 << 0,

    /**
     * Runs with a prefix. Requires SBR_DISCORDINTENT_MESSAGE_CONTENT intent to work properly
     * @deprecated Discord clearly wants to remove prefix based commands
     */
    SBR_COMMAND_TYPE_CLASSIC = 1 << 1,

    /**
     * Newer slash system
     */
    SBR_COMMAND_TYPE_SLASH = 1 << 2
} SBR_Command_Type;

typedef struct SBR_Command {
    const char* name;
    const char* description;
    SBR_Command_Type type;
    SBR_Command_Action Action;
} SBR_Command;

/**
 * 
 * @param name 
 * @param filter 0 will return any command that matches
 */
const SBR_Command* SBR_Command_Get(const char* name, SBR_Command_Type filter);
const BA_DynamicArray* SBR_Command_GetAll(void);

void SBR_Command_Initialize(void);
void SBR_Command_Register(const char* name, const char* description, SBR_Command_Type type, SBR_Command_Action Action);
void SBR_Command_Destroy(void);
