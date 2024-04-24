// Copyright (c) 2024, PortalPlayer <email@portalplayer.xyz>
// Licensed under MIT <https://opensource.org/licenses/MIT>

#include <BaconAPI/Internal/Boolean.h>
#include <BaconAPI/Debugging/Assert.h>

#include "WebSocket/cURL.h"

static CURL* sbrcURL;

CURL* SBR_cURL_Get(void) {
    return sbrcURL;
}

void SBR_cURL_Initialize(const char* url) {
    static BA_Boolean intialized = BA_BOOLEAN_FALSE;

    BA_ASSERT(!intialized, "Already initialized cURL\n");

    intialized = BA_BOOLEAN_TRUE;

    BA_ASSERT((sbrcURL = curl_easy_init()), "Failed to initialize cURL\n");
    curl_easy_setopt(sbrcURL, CURLOPT_URL, url != NULL ? url : DISCORD_WEBSOCKET_URL);
    curl_easy_setopt(sbrcURL, CURLOPT_CONNECT_ONLY, 2L);
    SBR_CURL_ASSERT(curl_easy_perform(sbrcURL), "Failed to perform cURL request: %s\n");
}

CURLcode SBR_cURL_Send(const void* data, const size_t size, size_t* sent, const unsigned int cURLFlag) {
    static size_t throwaway = 0;

    if (sent == NULL)
        sent = &throwaway;
    
    return curl_ws_send(sbrcURL, data, size, sent, 0, cURLFlag);
}
