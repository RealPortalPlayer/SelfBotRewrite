// Purpose: Base structure of a category
// Created on: 9/8/24 @ 9:17 AM

// Copyright (c) 2024, PortalPlayer <email@portalplayer.xyz>
// Licensed under MIT <https://opensource.org/licenses/MIT>

#pragma once

#include <BaconAPI/Storage/DynamicDictionary.h>

const char* SBR_Category_GetDescription(const char* name);
const BA_DynamicDictionary* SBR_Category_GetAll(void);

void SBR_Category_Initialize(void);
void SBR_Category_Register(const char* name, const char* description);
void SBR_Category_Destroy(void);
