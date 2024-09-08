// Copyright (c) 2024, PortalPlayer <email@portalplayer.xyz>
// Licensed under MIT <https://opensource.org/licenses/MIT>

#include <BaconAPI/Internal/Boolean.h>
#include <BaconAPI/ArgumentHandler.h>
#include <BaconAPI/Internal/OperatingSystem.h>

#if BA_OPERATINGSYSTEM_POSIX_COMPLIANT
#   include <unistd.h>
#   include <arpa/inet.h>
#elif BA_OPERATINGSYSTEM_WINDOWS
#   include <Windows.h>
#endif

#include <BaconAPI/Thread.h>
#include <string.h>
#include <stdint.h>
#include <BaconAPI/String.h>

#include "cURL.h"
#include "BuiltInArguments.h"
#include "Discord/Configuration.h"
#include "MainLoop.h"
#include "Token.h"
#include "UserAgent.h"

static CURL* sbrcURLWebSocket;
static BA_Boolean sbrcURLInitialized = BA_BOOLEAN_FALSE;
static BA_Thread_Lock sbrcURLLock;
static CURL* sbrcURLHTTP;
static char* sbrcURLAuthorizationHeader = NULL;

static size_t SBR_cURL_Write(char* buffer, size_t size, size_t newMemoryBytes, void* userPointer) {
    for (int i = 0; i < newMemoryBytes; i++)
        BA_String_AppendCharacter(userPointer, buffer[i]);
    
    return size * newMemoryBytes;
}

CURL* SBR_cURL_Get(void) {
    return sbrcURLWebSocket;
}

#define SBR_CURL_INITIALIZE(variable, type) \
BA_ASSERT((variable = curl_easy_init()), "Failed to initialize " type " cURL\n"); \
if (BA_ArgumentHandler_ContainsArgumentOrShort(SBR_BUILTINARGUMENTS_CURL_VERBOSE, SBR_BUILTINARGUMENTS_CURL_VERBOSE_SHORT, BA_BOOLEAN_FALSE)) \
    curl_easy_setopt(variable, CURLOPT_VERBOSE, 1L);

BA_Boolean SBR_cURL_Initialize(const char* webSocketUrl) {
    BA_ASSERT(!sbrcURLInitialized, "Already initialized cURL\n");
    BA_LOGGER_INFO("Starting cURL\n");
    
    sbrcURLInitialized = BA_BOOLEAN_TRUE;

    if (sbrcURLAuthorizationHeader == NULL) {
        sbrcURLAuthorizationHeader = BA_String_Copy("Authorization: Bot ");

        BA_ASSERT(sbrcURLAuthorizationHeader, "Failed to create authorization header\n");
        BA_String_Append(&sbrcURLAuthorizationHeader, SBR_Token_Get());
    }

    SBR_CURL_INITIALIZE(sbrcURLHTTP, "HTTP");
    curl_easy_setopt(sbrcURLHTTP, CURLOPT_USERAGENT, SBR_UserAgent_Get());
    curl_easy_setopt(sbrcURLHTTP, CURLOPT_WRITEFUNCTION, &SBR_cURL_Write);
    SBR_CURL_INITIALIZE(sbrcURLWebSocket, "WebSocket");
    BA_ASSERT(BA_Thread_CreateLock(&sbrcURLLock), "Failed to create cURL thread lock\n");
    curl_easy_setopt(sbrcURLWebSocket, CURLOPT_URL, webSocketUrl != NULL ? webSocketUrl : SBR_DiscordConfiguration_GetWebSocketURL());
    curl_easy_setopt(sbrcURLWebSocket, CURLOPT_CONNECT_ONLY, 2L);

    CURLcode code = curl_easy_perform(sbrcURLWebSocket);

    if (code == CURLE_OK)
        return BA_BOOLEAN_TRUE;

    sbrcURLInitialized = BA_BOOLEAN_FALSE;

    curl_easy_cleanup(sbrcURLHTTP);
    BA_LOGGER_ERROR("Failed to connect: %s\n", curl_easy_strerror(code));
    return BA_BOOLEAN_FALSE;
}

BA_Boolean SBR_cURL_WebSocketSend(const void* data, const size_t size, size_t* sent, const unsigned int cURLFlag) {
    size_t throwaway;

    BA_Thread_UseLock(&sbrcURLLock);
    
    if (cURLFlag == CURLWS_CLOSE && sbrcURLInitialized) {
        BA_LOGGER_WARN("Manual cURL close\n");

        sbrcURLInitialized = BA_BOOLEAN_FALSE;
    }
    
    if (sent == NULL)
        sent = &throwaway;

    CURLcode result = curl_ws_send(sbrcURLWebSocket, data, size, sent, 0, cURLFlag);

    if (cURLFlag == CURLWS_CLOSE) {
        SBR_CURL_ASSERT(result, "Failed to close cURL: %s\n");
        curl_easy_cleanup(sbrcURLWebSocket);
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

void SBR_cURL_Close(BA_Boolean success) {
    BA_ASSERT(sbrcURLInitialized, "cURL is not initialized\n");
    BA_LOGGER_INFO("Closing cURL\n");

    sbrcURLInitialized = BA_BOOLEAN_FALSE;

    char* codeCharacterPointer = malloc(sizeof(uint16_t));
    uint16_t code = htons(success ? 1000 : 4000);

    BA_ASSERT(codeCharacterPointer != NULL, "Failed to allocate closing code\n");
    memcpy(codeCharacterPointer, &code, sizeof(uint16_t));
    SBR_cURL_WebSocketSend(codeCharacterPointer, sizeof(uint16_t), NULL, CURLWS_CLOSE);
    curl_easy_cleanup(sbrcURLWebSocket);
    curl_easy_cleanup(sbrcURLHTTP);
    free(codeCharacterPointer);
    free(sbrcURLAuthorizationHeader);
    BA_Thread_DestroyLock(&sbrcURLLock);

    sbrcURLAuthorizationHeader = NULL;
}

BA_Boolean SBR_cURL_WebSocketReceive(void* buffer, size_t bufferSize, size_t* receivedBytes, const struct curl_ws_frame** metadata) {
    CURLcode result = curl_ws_recv(sbrcURLWebSocket, buffer, bufferSize, receivedBytes, metadata);

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

BA_Boolean SBR_cURL_HTTPSend(const char* url, const char* json, BA_Boolean post, char** response) {
    BA_Thread_UseLock(&sbrcURLLock);
    curl_easy_setopt(sbrcURLHTTP, CURLOPT_URL, url);
    curl_easy_setopt(sbrcURLHTTP, CURLOPT_WRITEDATA, response);
    curl_easy_setopt(sbrcURLHTTP, CURLOPT_POST, post);
    curl_easy_setopt(sbrcURLHTTP, CURLOPT_HTTPGET, !post);
    
    struct curl_slist* list = NULL;
    
    list = curl_slist_append(list, sbrcURLAuthorizationHeader);

    if (post) {
        list = curl_slist_append(list, "Content-Type: application/json");

        curl_easy_setopt(sbrcURLHTTP, CURLOPT_POSTFIELDS, json);
    }

    curl_easy_setopt(sbrcURLHTTP, CURLOPT_HTTPHEADER, list);
    // TODO: Don't crash
    SBR_CURL_ASSERT(curl_easy_perform(sbrcURLHTTP), "Failed to make HTTP request: %s\n");
    curl_slist_free_all(list);
    BA_Thread_Unlock(&sbrcURLLock);
    return BA_BOOLEAN_TRUE;
}

void SBR_cURL_LoopInitialize(const char* webSocketUrl) {
    int attempts = 0;
    
    while (BA_BOOLEAN_TRUE) {
        if (!SBR_cURL_Initialize(webSocketUrl)) {
            attempts++;
            
            BA_LOGGER_WARN("Retrying in 5 seconds...\n");
            sleep(5);
            continue;
        }

        break;
    }

    if (attempts == 0)
        return;

    BA_LOGGER_INFO("Finally connected after %i tries\n", attempts);
}
