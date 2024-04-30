// Copyright (c) 2024, PortalPlayer <email@portalplayer.xyz>
// Licensed under MIT <https://opensource.org/licenses/MIT>

#include <BaconAPI/Storage/DynamicArray.h>
#include <BaconAPI/Debugging/Assert.h>
#include <BaconAPI/String.h>
#include <BaconAPI/Math/Bitwise.h>

#include "Commands/Command.h"

static BA_DynamicArray* sbrCommandRegistered;
static BA_Boolean sbrCommandInitialized = BA_BOOLEAN_FALSE;

void SBR_Command_Initialize(void) {
    BA_ASSERT(!sbrCommandInitialized, "Command system are already initalized\n");
    BA_LOGGER_INFO("Initializing commands\n");
    
    sbrCommandInitialized = BA_BOOLEAN_TRUE;
    sbrCommandRegistered = malloc(sizeof(BA_DynamicArray));

    BA_ASSERT(sbrCommandRegistered != NULL, "Failed to allocate memory for registered commands\n");
    BA_ASSERT(BA_DynamicArray_Create(sbrCommandRegistered, 10), "Failed to initialize registered commands array\n");
}

void SBR_Command_Register(const char* name, const char* description, SBR_Command_Type type, SBR_Command_Action Action) {
    // TODO: Checks

    SBR_Command* command = malloc(sizeof(SBR_Command));

    BA_ASSERT(command != NULL, "Failed to allocate memory for command: %s\n", name);

    command->name = name;
    command->description = description;
    command->type = type;
    command->Action = Action;

    BA_ASSERT(BA_DynamicArray_AddElementToLast(sbrCommandRegistered, command), "Failed to add registered command\n");
}

const SBR_Command* SBR_Command_Get(const char* name, SBR_Command_Type filter) {
    for (int i = 0; i < sbrCommandRegistered->used; i++) {
        const SBR_Command* command = BA_DYNAMICARRAY_GET_ELEMENT_POINTER(SBR_Command, sbrCommandRegistered, i);
        
        if (!BA_String_Equals(command->name, name, BA_BOOLEAN_TRUE) || !BA_BITWISE_IS_BIT_SET(command->type, filter))
            continue;

        return command;
    }

    return NULL;
}

void SBR_Command_Destroy(void) {
    BA_ASSERT(sbrCommandInitialized, "Command system is not initialized\n");
    BA_LOGGER_INFO("Destroying commands\n");

    sbrCommandInitialized = BA_BOOLEAN_FALSE;

    for (int i = 0; i < sbrCommandRegistered->used; i++)
        free(sbrCommandRegistered->internalArray[i]);

    free(sbrCommandRegistered->internalArray);
    free(sbrCommandRegistered);
}

const BA_DynamicArray* SBR_Command_GetAll(void) {
    return sbrCommandRegistered;
}
