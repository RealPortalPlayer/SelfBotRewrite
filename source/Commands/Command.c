// Copyright (c) 2024, PortalPlayer <email@portalplayer.xyz>
// Licensed under MIT <https://opensource.org/licenses/MIT>

#include <BaconAPI/String.h>
#include <BaconAPI/Math/Bitwise.h>
#include <BaconAPI/ArgumentHandler.h>

#include "Commands/Command.h"
#include "BuiltInArguments.h"
#include "Storage/DynamicArray.h"
#include "Memory.h"
#include "Debugging/Assert.h"

static BA_DynamicArray sbrCommandRegistered;
static BA_Boolean sbrCommandInitialized = BA_BOOLEAN_FALSE;

void SBR_Command_Initialize(void) {
    SBR_ASSERT(!sbrCommandInitialized, "Command system are already initialized\n");
    BA_LOGGER_INFO("Initializing commands\n");
    
    sbrCommandInitialized = BA_BOOLEAN_TRUE;

    SBR_ASSERT(SBR_DynamicArray_Create(&sbrCommandRegistered, 10), "Failed to initialize registered commands array\n");
}

void SBR_Command_Register(const char* name, const char* description, const char* categoryName, SBR_Command_Type type, SBR_Command_Action Action) {
    // TODO: Checks

    static BA_Boolean terminalCommandsDisabled = -1;
    static BA_Boolean slashCommandsDisabled = -1;
    static BA_Boolean classicCommandsDisabled = -1;

    if (terminalCommandsDisabled == -1) {
        terminalCommandsDisabled = BA_ArgumentHandler_ContainsArgumentOrShort(SBR_BUILTINARGUMENTS_DISABLE_TERMINAL_COMMANDS, SBR_BUILTINARGUMENTS_DISABLE_TERMINAL_COMMANDS_SHORT, BA_BOOLEAN_FALSE);
        slashCommandsDisabled = BA_ArgumentHandler_ContainsArgumentOrShort(SBR_BUILTINARGUMENTS_DISABLE_SLASH_COMMANDS, SBR_BUILTINARGUMENTS_DISABLE_SLASH_COMMANDS_SHORT, BA_BOOLEAN_FALSE);
        classicCommandsDisabled = BA_ArgumentHandler_ContainsArgumentOrShort(SBR_BUILTINARGUMENTS_DISABLE_CLASSIC_COMMANDS, SBR_BUILTINARGUMENTS_DISABLE_CLASSIC_COMMANDS_SHORT, BA_BOOLEAN_FALSE);
    }
    
    SBR_Command* command = BA_Memory_Allocate(sizeof(SBR_Command), SBR_MEMORY_TYPE_COMMAND);
    
    command->name = name;
    command->description = description;
    command->categoryName = categoryName;
    command->type = type;
    command->Action = Action;

#define SBR_COMMAND_CHECK_FOR_DISABLED_TYPE(check, removedType) \
do {                                                        \
    if (check && BA_BITWISE_IS_BIT_SET(command->type, removedType)) { \
        BA_BITWISE_UNSET_BIT(command->type, removedType);   \
        if (command->type == 0) {                           \
            free(command);                                  \
            return;                                         \
        }                                                   \
    }                                                       \
} while (BA_BOOLEAN_FALSE)

    SBR_COMMAND_CHECK_FOR_DISABLED_TYPE(terminalCommandsDisabled, SBR_COMMAND_TYPE_TERMINAL);
    SBR_COMMAND_CHECK_FOR_DISABLED_TYPE(slashCommandsDisabled, SBR_COMMAND_TYPE_SLASH);
    SBR_COMMAND_CHECK_FOR_DISABLED_TYPE(classicCommandsDisabled, SBR_COMMAND_TYPE_CLASSIC);
    SBR_DynamicArray_CheckResize(&sbrCommandRegistered);
    SBR_ASSERT(BA_DynamicArray_AddElementToLast(&sbrCommandRegistered, command), "Failed to add registered command\n");
}

const SBR_Command* SBR_Command_Get(const char* name, SBR_Command_Type filter) {
    for (int i = 0; i < sbrCommandRegistered.used; i++) {
        const SBR_Command* command = BA_DYNAMICARRAY_GET_ELEMENT(SBR_Command, sbrCommandRegistered, i);
        
        if (!BA_String_Equals(command->name, name, BA_BOOLEAN_TRUE) || !BA_BITWISE_IS_BIT_SET(command->type, filter))
            continue;

        return command;
    }

    return NULL;
}

void SBR_Command_Destroy(void) {
    SBR_ASSERT(sbrCommandInitialized, "Command system is not initialized\n");
    BA_LOGGER_INFO("Destroying commands\n");

    sbrCommandInitialized = BA_BOOLEAN_FALSE;

    for (int i = 0; i < sbrCommandRegistered.used; i++)
        BA_Memory_Deallocate(sbrCommandRegistered.internalArray[i], sizeof(SBR_Command), SBR_MEMORY_TYPE_COMMAND);

    BA_Memory_Deallocate(sbrCommandRegistered.internalArray, sizeof(void*) * sbrCommandRegistered.size, SBR_MEMORY_TYPE_DYNAMIC_ARRAY);
}

const BA_DynamicArray* SBR_Command_GetAll(void) {
    return &sbrCommandRegistered;
}
