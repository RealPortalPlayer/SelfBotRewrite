// Purpose: DynamicDictionary wrapper that uses the memory system
// Created on: 9/9/24 @ 11:40 PM

// Copyright (c) 2024, PortalPlayer <email@portalplayer.xyz>
// Licensed under MIT <https://opensource.org/licenses/MIT>

#pragma once

#include <BaconAPI/Internal/Boolean.h>
#include <BaconAPI/Storage/DynamicDictionary.h>

BA_Boolean SBR_DynamicDictionary_Create(BA_DynamicDictionary* dictionary, size_t size);
