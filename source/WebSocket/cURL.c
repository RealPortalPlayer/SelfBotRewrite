// Copyright (c) 2024, PortalPlayer <email@portalplayer.xyz>
// Licensed under MIT <https://opensource.org/licenses/MIT>

#include <BaconAPI/Internal/Boolean.h>
#include <BaconAPI/ArgumentHandler.h>

#include "WebSocket/cURL.h"
#include "BuiltInArguments.h"
#include "Discord/Configuration.h"

static CURL* sbrcURL;
static BA_Boolean sbrcURLInitialized = BA_BOOLEAN_FALSE;

CURL* SBR_cURL_Get(void) {
    return sbrcURL;
}

void SBR_cURL_Initialize(const char* url) {
    BA_ASSERT(!sbrcURLInitialized, "Already initialized cURL\n");

    sbrcURLInitialized = BA_BOOLEAN_TRUE;

    BA_ASSERT((sbrcURL = curl_easy_init()), "Failed to initialize cURL\n");

    if (BA_ArgumentHandler_ContainsArgumentOrShort(SBR_BUILTINARGUMENTS_CURL_VERBOSE, SBR_BUILTINARGUMENTS_CURL_VERBOSE_SHORT, BA_BOOLEAN_FALSE))
        curl_easy_setopt(sbrcURL, CURLOPT_VERBOSE, 1L);
    
    curl_easy_setopt(sbrcURL, CURLOPT_URL, url != NULL ? url : SBR_DiscordConfiguration_GetWebSocketURL());
    curl_easy_setopt(sbrcURL, CURLOPT_CONNECT_ONLY, 2L);
    SBR_CURL_ASSERT(curl_easy_perform(sbrcURL), "Failed to perform cURL request: %s\n");
}

CURLcode SBR_cURL_Send(const void* data, const size_t size, size_t* sent, const unsigned int cURLFlag) {
    size_t throwaway;

    if (cURLFlag == CURLWS_CLOSE && sbrcURLInitialized) {
        BA_LOGGER_WARN("Manual cURL close\n");

        sbrcURLInitialized = BA_BOOLEAN_FALSE;
    }
    
    if (sent == NULL)
        sent = &throwaway;

    CURLcode result = curl_ws_send(sbrcURL, data, size, sent, 0, cURLFlag);

    if (cURLFlag == CURLWS_CLOSE) {
        SBR_CURL_ASSERT(result, "Failed to close cURL: %s\n");
        curl_easy_cleanup(sbrcURL);
    }
    
    return result;
}

void SBR_cURL_Close(void) {
    BA_ASSERT(sbrcURLInitialized, "cURL is not initialized\n");

    sbrcURLInitialized = BA_BOOLEAN_FALSE;

    SBR_cURL_Send("", 0, NULL, CURLWS_CLOSE);
    curl_easy_cleanup(sbrcURL);
}

BA_Boolean SRB_cURL_Recieve(void* buffer, size_t bufferSize, size_t* receivedBytes, const struct curl_ws_frame** metadata) {
    CURLcode result = curl_ws_recv(sbrcURL, buffer, bufferSize, receivedBytes, metadata);

    if (result == CURLE_AGAIN) {
        BA_LOGGER_TRACE("cURL buffer dry\n");
        // TODO: Mark connection as cold after x amount of empty buffers
        return BA_BOOLEAN_FALSE;
    }

    SBR_CURL_ASSERT(result, "Failed to receive buffer: %s\n");
    return BA_BOOLEAN_TRUE;
}
