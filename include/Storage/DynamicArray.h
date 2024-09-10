// Purpose: DynamicArray wrapper that uses the memory system
// Created on: 9/9/24 @ 11:35 PM

// Copyright (c) 2024, PortalPlayer <email@portalplayer.xyz>
// Licensed under MIT <https://opensource.org/licenses/MIT>

#pragma once

#include <BaconAPI/Internal/Boolean.h>
#include <BaconAPI/Storage/DynamicArray.h>

BA_Boolean SBR_DynamicArray_Create(BA_DynamicArray* array, size_t size);
BA_Boolean SBR_DynamicArray_CheckResize(BA_DynamicArray* array);
