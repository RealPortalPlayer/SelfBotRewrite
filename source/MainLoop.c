// Copyright (c) 2024, PortalPlayer <email@portalplayer.xyz>
// Licensed under MIT <https://opensource.org/licenses/MIT>

#include <BaconAPI/Logger.h>
#include <BaconAPI/Internal/OperatingSystem.h>

#if BA_OPERATINGSYSTEM_POSIX_COMPLIANT
#   include <unistd.h>
#elif BA_OPERATINGSYSTEM_WINDOWS
#   include <Windows.h>
#endif

#include "MainLoop.h"
#include "WebSocket/cURL.h"
#include "Discord/Gateway/Event.h"
#include "Discord/Gateway/Gateway.h"

#define SBR_MAIN_PACKET_BUFFER_SIZE 9000 // TODO: Get a more concrete number

static volatile BA_Boolean sbrMainDisconnected = BA_BOOLEAN_FALSE;

BA_Boolean SBR_MainLoop_Start(void) {
#ifndef SBR_STATIC
    BA_LOGGER_INFO("Starting cURL\n");

    {
        BA_Boolean errored = BA_BOOLEAN_FALSE;

        while (BA_BOOLEAN_TRUE) {
            if (!SBR_cURL_Initialize(NULL)) {
                errored = BA_BOOLEAN_TRUE;
                
                BA_LOGGER_WARN("Retrying in 5 seconds...\n");
                sleep(5);
                continue;
            }

            break;
        }
        
        if (errored)
            BA_LOGGER_INFO("Finally connected\n");
    }

    sbrMainDisconnected = BA_BOOLEAN_FALSE;
    
    while (BA_BOOLEAN_TRUE) {
        char buffer[SBR_MAIN_PACKET_BUFFER_SIZE];
        size_t receivedBytes;
        const struct curl_ws_frame* metadata;

        if (!SBR_cURL_Receive(buffer, SBR_MAIN_PACKET_BUFFER_SIZE, &receivedBytes, &metadata)) {
            if (sbrMainDisconnected)
                break;

            continue;
        }

        buffer[receivedBytes] = '\0';

        SBR_Gateway_Parse(buffer);
    }

    BA_LOGGER_INFO("Closing cURL\n");
    SBR_cURL_Close();
    return !sbrMainDisconnected;
#else
    BA_LOGGER_WARN("You're not supposed to call this\n");
    return BA_BOOLEAN_TRUE;
#endif
}

void SBR_MainLoop_SignalDisconnected(void) {
    sbrMainDisconnected = BA_BOOLEAN_TRUE;
}
