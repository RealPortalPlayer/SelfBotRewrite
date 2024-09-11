// Purpose: BaconAPI assert wrapper
// Created on: 9/11/24 @ 4:02 PM

// Copyright (c) 2024, PortalPlayer <email@portalplayer.xyz>
// Licensed under MIT <https://opensource.org/licenses/MIT>

#pragma once

#include <BaconAPI/Debugging/Assert.h>

const char* SBR_Assert_GetCode(void);
const char* SBR_Assert_GetMessage(void);

void SBR_Assert_Set(const char* code, const char* message, ...);

#define SBR_ASSERT(check, ...) \
do {                           \
    SBR_Assert_Set(#check, __VA_ARGS__); \
    BA_ASSERT(check, __VA_ARGS__); \
} while (BA_BOOLEAN_FALSE)

#define SBR_ASSERT_ALWAYS(...) SBR_ASSERT(BA_BOOLEAN_FALSE, __VA_ARGS__)
#define SBR_ASSERT_NOT_IMPLEMENTED() SBR_ASSERT_ALWAYS("This function is currently not implemented\n")
