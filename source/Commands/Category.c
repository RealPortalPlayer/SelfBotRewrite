// Copyright (c) 2024, PortalPlayer <email@portalplayer.xyz>
// Licensed under MIT <https://opensource.org/licenses/MIT>

#include <string.h>
#include <BaconAPI/Debugging/Assert.h>
#include <BaconAPI/Logger.h>

#include "Commands/Category.h"

static BA_DynamicDictionary* sbrCategoryRegistered;
static BA_Boolean sbrCategoryInitialized = BA_BOOLEAN_FALSE;

const char* SBR_Category_GetDescription(const char* name) {
    return BA_DynamicDictionary_GetElementValueViaKey(sbrCategoryRegistered, name, sizeof(char) * (strlen(name) + 1));
}

const BA_DynamicDictionary* SBR_Category_GetAll(void) {
    return sbrCategoryRegistered;
}

void SBR_Category_Initialize(void) {
    BA_ASSERT(!sbrCategoryRegistered, "Category system are already initialized\n");
    BA_LOGGER_INFO("Initializing categories\n");

    sbrCategoryInitialized = BA_BOOLEAN_TRUE;
    sbrCategoryRegistered = malloc(sizeof(BA_DynamicDictionary));

    BA_ASSERT(sbrCategoryRegistered != NULL, "Failed to allocate memory for registered categories\n");
    BA_ASSERT(BA_DynamicDictionary_Create(sbrCategoryRegistered, 10), "Failed to initialize registered categories array\n");
}

void SBR_Category_Register(const char* name, const char* description) {
    BA_ASSERT(BA_DynamicDictionary_AddElementToLast(sbrCategoryRegistered, (void*) name, (void*) description), "Failed to add registered category\n");
}

void SBR_Category_Destroy(void) {
    BA_ASSERT(sbrCategoryInitialized, "Category system is not initialized\n");
    BA_LOGGER_INFO("Destroying categories\n");

    sbrCategoryInitialized = BA_BOOLEAN_FALSE;

    free(sbrCategoryRegistered->keys.internalArray);
    free(sbrCategoryRegistered->values.internalArray);
    free(sbrCategoryRegistered);
}
