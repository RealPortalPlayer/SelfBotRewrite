// Copyright (c) 2024, PortalPlayer <email@portalplayer.xyz>
// Licensed under MIT <https://opensource.org/licenses/MIT>

#include <BaconAPI/String.h>
#include <BaconAPI/Math/Bitwise.h>
#include <BaconAPI/Internal/OperatingSystem.h>
#include <BaconAPI/Internal/Compiler.h>

#include "DebugInformation.h"
#include "Commands/Command.h"
#include "Commands/Category.h"

char* SBR_DebugInformation_Get(void) {
    char* debugMessage = BA_String_Copy("Terminal commands: %i\n"
                                        "Classic categories: %i\n"
                                        "Classic commands: %i\n"
                                        "Slash commands: %i\n"
                                        "Version: %s\n"
                                        "OS: %s\n"
                                        "C standard version: %i");

    int terminalCommands = 0;
    int classicCommands = 0;
    int slashCommands = 0;

    {
        const BA_DynamicArray* registeredCommands = SBR_Command_GetAll();

        for (int i = 0; i < registeredCommands->used; i++) {
            SBR_Command* command = BA_DYNAMICARRAY_GET_ELEMENT_POINTER(SBR_Command, registeredCommands, i);

            if (BA_BITWISE_IS_BIT_SET(command->type, SBR_COMMAND_TYPE_TERMINAL))
                terminalCommands++;
            else if (BA_BITWISE_IS_BIT_SET(command->type, SBR_COMMAND_TYPE_CLASSIC))
                classicCommands++;
            else if (BA_BITWISE_SET_BIT(command->type, SBR_COMMAND_TYPE_SLASH))
                slashCommands++;
        }
    }

    return BA_String_Format(&debugMessage, terminalCommands,
                                           SBR_Category_GetAll()->keys.used,
                                           classicCommands,
                                           slashCommands,
                                           SBR_VERSION,
                                           BA_OPERATINGSYSTEM_NAME,
                                           BA_COMPILER_STANDARD_VERSION);
}
