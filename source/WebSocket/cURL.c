// Copyright (c) 2024, PortalPlayer <email@portalplayer.xyz>
// Licensed under MIT <https://opensource.org/licenses/MIT>

#include <BaconAPI/Internal/Boolean.h>
#include <BaconAPI/Debugging/Assert.h>

#include "WebSocket/cURL.h"

static CURL* sbrcURL;

CURL* SBR_cURL_Get(void) {
    return sbrcURL;
}

void SBR_cURL_Initialize(void) {
    static BA_Boolean intialized = BA_BOOLEAN_FALSE;

    BA_ASSERT(!intialized, "Already initialized cURL\n");

    intialized = BA_BOOLEAN_TRUE;

    BA_ASSERT((sbrcURL = curl_easy_init()), "Failed to initialize cURL\n");
    curl_easy_setopt(sbrcURL, CURLOPT_URL, "ws://127.0.0.1:1234");
    curl_easy_setopt(sbrcURL, CURLOPT_CONNECT_ONLY, 2L);
    
    {
        CURLcode response = curl_easy_perform(sbrcURL);

        BA_ASSERT(response == CURLE_OK, "Failed to perform cURL request: %s\n", curl_easy_strerror(response));
    }
}

CURLcode SBR_cURL_Send(const void* data, const size_t size, size_t* sent, const unsigned int cURLFlag) {
    static size_t throwaway = 0;

    if (sent == NULL)
        sent = &throwaway;
    
    return curl_ws_send(sbrcURL, data, size, sent, 0, cURLFlag);
}
