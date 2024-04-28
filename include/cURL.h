// Copyright (c) 2024, PortalPlayer <email@portalplayer.xyz>
// Licensed under MIT <https://opensource.org/licenses/MIT>

// Purpose: WebSocket wrapper around cURL
// Created on: 4/23/24 @ 4:17 PM


#pragma once

#include <curl/curl.h>
#include <BaconAPI/Debugging/Assert.h>

CURL* SBR_cURL_Get(void);

BA_Boolean SBR_cURL_Initialize(const char* webSocketUrl);
BA_Boolean SBR_cURL_WebSocketSend(const void* data, size_t size, size_t* sent, unsigned int cURLFlag);
void SBR_cURL_Close(BA_Boolean success);
BA_Boolean SBR_cURL_WebSocketReceive(void* buffer, size_t bufferSize, size_t* receivedBytes, const struct curl_ws_frame** metadata);
BA_Boolean SBR_cURL_HTTPSend(const char* url, const char* json, BA_Boolean post, char** response);
void SBR_cURL_LooopInitialize(const char* webSocketUrl);

#define SBR_CURL_ASSERT(call, message) \
do {                               \
    CURLcode sbrcURLCodePaddingToPreventNameCollisionsPleaseDontCollidePlease = call; \
    BA_ASSERT(sbrcURLCodePaddingToPreventNameCollisionsPleaseDontCollidePlease == CURLE_OK, message, curl_easy_strerror(sbrcURLCodePaddingToPreventNameCollisionsPleaseDontCollidePlease)); \
} while (BA_BOOLEAN_FALSE)
