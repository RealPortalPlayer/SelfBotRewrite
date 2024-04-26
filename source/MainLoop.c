// Copyright (c) 2024, PortalPlayer <email@portalplayer.xyz>
// Licensed under MIT <https://opensource.org/licenses/MIT>

#include <BaconAPI/Logger.h>
#include <BaconAPI/Internal/OperatingSystem.h>

#if BA_OPERATINGSYSTEM_POSIX_COMPLIANT
#   include <unistd.h>
#   include <arpa/inet.h>
#elif BA_OPERATINGSYSTEM_WINDOWS
#   include <Windows.h>
#endif

#include <BaconAPI/Math/Bitwise.h>
#include <string.h>
#include <curl/curl.h>

#include "MainLoop.h"

#include <BuiltInArguments.h>
#include <BaconAPI/ArgumentHandler.h>
#include <BaconAPI/Number.h>

#include "WebSocket/cURL.h"
#include "Discord/Gateway/Event.h"
#include "Discord/Gateway/Gateway.h"
#include "Discord/Gateway/Error.h"
#include "Threads/Heartbeat.h"

#define SBR_MAINLOOP_START_CURL() \
do {                              \
    BA_LOGGER_INFO("Starting cURL\n"); \
    BA_Boolean errored = BA_BOOLEAN_FALSE; \
    while (BA_BOOLEAN_TRUE) {     \
        if (!SBR_cURL_Initialize(NULL)) { \
            errored = BA_BOOLEAN_TRUE; \
            BA_LOGGER_WARN("Retrying in 5 seconds...\n"); \
            sleep(5);             \
            continue;             \
        }                         \
        break;                    \
    }                             \
    if (errored)                  \
        BA_LOGGER_INFO("Finally connected\n"); \
} while (BA_BOOLEAN_FALSE)

static volatile BA_Boolean sbrMainDisconnected = BA_BOOLEAN_FALSE;
static volatile BA_Boolean sbrMainShuttingDown = BA_BOOLEAN_FALSE;

BA_Boolean SBR_MainLoop_Start(void) {
#ifndef SBR_STATIC
    static int bufferSize = -1;

    if (bufferSize == -1) {
        BA_ArgumentHandler_ShortResults results;

        if (BA_ArgumentHandler_GetInformationWithShort(SBR_BUILTINARGUMENTS_EVENT_BUFFER, SBR_BUILTINARGUMENTS_EVENT_BUFFER_SHORT, BA_BOOLEAN_FALSE, &results) != 0)
            bufferSize = BA_Number_StringToInteger(*results.value, NULL, NULL, "Invalid event buffer number\n", 9000);
        else
            bufferSize = 9000;

        BA_LOGGER_DEBUG("Event buffer size: %i character(s)\n", bufferSize);
    }
    
    SBR_MAINLOOP_START_CURL();
    
    sbrMainDisconnected = BA_BOOLEAN_FALSE;
    
    while (!SBR_MainLoop_IsShuttingDown()) {
        char buffer[bufferSize];
        size_t receivedBytes;
        const struct curl_ws_frame* metadata;

        if (!SBR_cURL_Receive(buffer, bufferSize, &receivedBytes, &metadata)) {
            if (sbrMainDisconnected)
                break;

            continue;
        }

        buffer[receivedBytes] = '\0';

        if (BA_BITWISE_IS_BIT_SET(metadata->flags, CURLWS_CLOSE)) {
            uint16_t code = 0;
            char message[receivedBytes - sizeof(uint16_t)];

            memcpy(&code, buffer, sizeof(uint16_t));
            memcpy(&message, buffer + sizeof(uint16_t), sizeof(char) * receivedBytes);
            
            code = ntohs(code);

            SBR_Gateway_ParseError(code, message);

            if (!SBR_GatewayError_CanReconnect(code)) {
                BA_LOGGER_INFO("Cannot reconnect, restarting bot\n");
                SBR_MainLoop_SignalDisconnected();
                break;
            }

            BA_LOGGER_INFO("Closing cURL\n");
            SBR_HeartbeatThread_Pause(BA_BOOLEAN_TRUE);
            SBR_cURL_Close(BA_BOOLEAN_FALSE);
            SBR_MAINLOOP_START_CURL();
            BA_ASSERT_NOT_IMPLEMENTED(); // TODO: Resume
            continue;
        }
        
        SBR_Gateway_Parse(buffer);
    }

    BA_LOGGER_INFO("Closing cURL\n");
    SBR_cURL_Close(BA_BOOLEAN_TRUE);
    return !sbrMainDisconnected;
#else
    BA_LOGGER_WARN("You're not supposed to call this\n");
    return BA_BOOLEAN_TRUE;
#endif
}

void SBR_MainLoop_SignalDisconnected(void) {
    sbrMainDisconnected = BA_BOOLEAN_TRUE;
}

void SBR_MainLoop_Shutdown(void) {
    sbrMainShuttingDown = BA_BOOLEAN_TRUE;
}

BA_Boolean SBR_MainLoop_IsShuttingDown(void) {
    return sbrMainShuttingDown;
}
