// Copyright (c) 2024, PortalPlayer <email@portalplayer.xyz>
// Licensed under MIT <https://opensource.org/licenses/MIT>

#include <BaconAPI/Debugging/Assert.h>

#include "Storage/DynamicArray.h"
#include "Memory.h"

BA_Boolean SBR_DynamicArray_Create(BA_DynamicArray* array, size_t size) {
    if (size <= 0)
        return BA_BOOLEAN_FALSE;

    array->internalArray = (void**) BA_Memory_Allocate(sizeof(void*) * size, SBR_MEMORY_TYPE_DYNAMIC_ARRAY);
    array->used = 0;
    array->size = size;
    array->frozen = BA_BOOLEAN_FALSE;
    return BA_BOOLEAN_TRUE;
}

BA_Boolean SBR_DynamicArray_CheckResize(BA_DynamicArray* array) {
    if (array->size != (size_t) array->used)
        return BA_BOOLEAN_TRUE;

    BA_LOGGER_TRACE("Ran out of free space, expanding array\nThis is expensive, so you should try avoiding it\n");
    BA_ASSERT((int) array->size >= array->used, "Invalid array state\n");

    array->size *= 2;
    array->calledReallocate++;
    
    void** newArray = BA_Memory_Reallocate(array->internalArray, sizeof(void*) * (array->size / 2), sizeof(void*) * array->size, SBR_MEMORY_TYPE_DYNAMIC_ARRAY);

    if (newArray == NULL)
        return BA_BOOLEAN_FALSE;
    
    array->internalArray = newArray;
    return BA_BOOLEAN_TRUE;
}
