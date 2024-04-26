// Copyright (c) 2024, PortalPlayer <email@portalplayer.xyz>
// Licensed under MIT <https://opensource.org/licenses/MIT>

#include <BaconAPI/Internal/Boolean.h>
#include <BaconAPI/ArgumentHandler.h>
#include <BaconAPI/Internal/OperatingSystem.h>

#if BA_OPERATINGSYSTEM_POSIX_COMPLIANT
#   include <unistd.h>
#elif BA_OPERATINGSYSTEM_WINDOWS
#   include <Windows.h>
#endif

#include <BaconAPI/Thread.h>

#include "WebSocket/cURL.h"
#include "BuiltInArguments.h"
#include "Discord/Configuration.h"
#include "MainLoop.h"

static CURL* sbrcURL;
static BA_Boolean sbrcURLInitialized = BA_BOOLEAN_FALSE;
static BA_Thread_Lock sbrcURLLock;

CURL* SBR_cURL_Get(void) {
    return sbrcURL;
}

BA_Boolean SBR_cURL_Initialize(const char* url) {
    BA_ASSERT(!sbrcURLInitialized, "Already initialized cURL\n");

    sbrcURLInitialized = BA_BOOLEAN_TRUE;

    BA_ASSERT(BA_Thread_CreateLock(&sbrcURLLock), "Failed to create cURL thread lock\n");
    BA_ASSERT((sbrcURL = curl_easy_init()), "Failed to initialize cURL\n");

    if (BA_ArgumentHandler_ContainsArgumentOrShort(SBR_BUILTINARGUMENTS_CURL_VERBOSE, SBR_BUILTINARGUMENTS_CURL_VERBOSE_SHORT, BA_BOOLEAN_FALSE))
        curl_easy_setopt(sbrcURL, CURLOPT_VERBOSE, 1L);
    
    curl_easy_setopt(sbrcURL, CURLOPT_URL, url != NULL ? url : SBR_DiscordConfiguration_GetWebSocketURL());
    curl_easy_setopt(sbrcURL, CURLOPT_CONNECT_ONLY, 2L);

    CURLcode code = curl_easy_perform(sbrcURL);

    if (code == CURLE_OK)
        return BA_BOOLEAN_TRUE;

    sbrcURLInitialized = BA_BOOLEAN_FALSE;
    
    BA_LOGGER_ERROR("Failed to connect: %s\n", curl_easy_strerror(code));
    return BA_BOOLEAN_FALSE;
}

BA_Boolean SBR_cURL_Send(const void* data, const size_t size, size_t* sent, const unsigned int cURLFlag) {
    size_t throwaway;

    BA_Thread_UseLock(&sbrcURLLock);
    
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

    if (result == CURLE_OK) {
        BA_Thread_Unlock(&sbrcURLLock);
        return BA_BOOLEAN_TRUE;
    }
    
    BA_LOGGER_ERROR("Failed to send message (%i): %s\n", cURLFlag, curl_easy_strerror(result));
    SBR_MainLoop_SignalDisconnected(); // TODO: Is this really required?
    BA_Thread_Unlock(&sbrcURLLock);
    return BA_BOOLEAN_FALSE;
}

void SBR_cURL_Close(void) {
    BA_ASSERT(sbrcURLInitialized, "cURL is not initialized\n");

    sbrcURLInitialized = BA_BOOLEAN_FALSE;

    SBR_cURL_Send("", 0, NULL, CURLWS_CLOSE);
    curl_easy_cleanup(sbrcURL);
}

BA_Boolean SBR_cURL_Receive(void* buffer, size_t bufferSize, size_t* receivedBytes, const struct curl_ws_frame** metadata) {
    CURLcode result = curl_ws_recv(sbrcURL, buffer, bufferSize, receivedBytes, metadata);

    if (result == CURLE_AGAIN) {
        // BA_LOGGER_TRACE("cURL buffer dry\n");
        return BA_BOOLEAN_FALSE;
    }

    if (result == CURLE_GOT_NOTHING) {
        BA_LOGGER_ERROR("Connection closed\n");
        SBR_MainLoop_SignalDisconnected();
        return BA_BOOLEAN_FALSE;
    }

    if (result == CURLE_RECV_ERROR) {
        BA_LOGGER_ERROR("Error occurred while receiving buffer\n");
        SBR_MainLoop_SignalDisconnected();
        return BA_BOOLEAN_FALSE;
    }

    SBR_CURL_ASSERT(result, "Failed to receive buffer: %s\n");
    return BA_BOOLEAN_TRUE;
}
