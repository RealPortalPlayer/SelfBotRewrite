// Purpose: WebSocket wrapper around cURL
// Created on: 4/23/24 @ 4:17 PM


// Copyright (c) 2024, PortalPlayer <email@portalplayer.xyz>
// Licensed under MIT <https://opensource.org/licenses/MIT>

#pragma once

#include <curl/curl.h>
#include <BaconAPI/Debugging/Assert.h>

CURL* SBR_cURL_Get(void);

void SBR_cURL_Initialize(const char* url);
CURLcode SBR_cURL_Send(const void* data, const size_t size, size_t* sent, unsigned int cURLFlag);

#define SBR_CURL_ASSERT(call, message) \
do {                               \
    CURLcode sbrcURLCodePaddingToPreventNameCollisionsPleaseDontCollidePlease = call; \
    BA_ASSERT(sbrcURLCodePaddingToPreventNameCollisionsPleaseDontCollidePlease == CURLE_OK, message, curl_easy_strerror(sbrcURLCodePaddingToPreventNameCollisionsPleaseDontCollidePlease)); \
} while (BA_BOOLEAN_FALSE)
