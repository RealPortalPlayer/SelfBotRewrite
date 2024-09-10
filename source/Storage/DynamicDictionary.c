// Copyright (c) 2024, PortalPlayer <email@portalplayer.xyz>
// Licensed under MIT <https://opensource.org/licenses/MIT>

#include "Storage/DynamicDictionary.h"
#include "Storage/DynamicArray.h"

BA_Boolean SBR_DynamicDictionary_Create(BA_DynamicDictionary* dictionary, size_t size) {
    BA_Boolean returnValue = SBR_DynamicArray_Create(&dictionary->keys, size) && SBR_DynamicArray_Create(&dictionary->values, size);

    dictionary->frozen = BA_BOOLEAN_FALSE;
    return returnValue;
}
