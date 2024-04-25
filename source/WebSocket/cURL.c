// Copyright (c) 2024, PortalPlayer <email@portalplayer.xyz>
// Licensed under MIT <https://opensource.org/licenses/MIT>

#include <BaconAPI/Internal/Boolean.h>
#include <BaconAPI/ArgumentHandler.h>

#include "WebSocket/cURL.h"
#include "BuiltInArguments.h"
#include "Discord/Configuration.h"

static CURL* sbrcURL;

CURL* SBR_cURL_Get(void) {
    return sbrcURL;
}

void SBR_cURL_Initialize(const char* url) {
    static BA_Boolean intialized = BA_BOOLEAN_FALSE;

    BA_ASSERT(!intialized, "Already initialized cURL\n");

    intialized = BA_BOOLEAN_TRUE;

    BA_ASSERT((sbrcURL = curl_easy_init()), "Failed to initialize cURL\n");

    if (BA_ArgumentHandler_ContainsArgumentOrShort(SBR_BUILTINARGUMENTS_CURL_VERBOSE, SBR_BUILTINARGUMENTS_CURL_VERBOSE_SHORT, BA_BOOLEAN_FALSE))
        curl_easy_setopt(sbrcURL, CURLOPT_VERBOSE, 1L);
    
    curl_easy_setopt(sbrcURL, CURLOPT_URL, url != NULL ? url : SBR_DiscordConfiguration_GetWebSocketURL());
    curl_easy_setopt(sbrcURL, CURLOPT_CONNECT_ONLY, 2L);
    SBR_CURL_ASSERT(curl_easy_perform(sbrcURL), "Failed to perform cURL request: %s\n");
}

CURLcode SBR_cURL_Send(const void* data, const size_t size, size_t* sent, const unsigned int cURLFlag) {
    static size_t throwaway = 0;

    if (sent == NULL)
        sent = &throwaway;
    
    return curl_ws_send(sbrcURL, data, size, sent, 0, cURLFlag);
}
