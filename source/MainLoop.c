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
#include <BuiltInArguments.h>
#include <BaconAPI/ArgumentHandler.h>
#include <BaconAPI/Number.h>
#include <BaconAPI/String.h>

#include "MainLoop.h"
#include "cURL.h"
#include "Discord/Gateway/Event.h"
#include "Discord/Gateway/Gateway.h"
#include "Discord/Gateway/Error.h"
#include "Threads/Heartbeat.h"
#include "Discord/Gateway/Events.h"
#include "Memory.h"
#include "Bot.h"
#include "SupportChannels.h"

static volatile BA_Boolean sbrMainLoopDisconnected = BA_BOOLEAN_FALSE;
static volatile BA_Boolean sbrMainLoopShuttingDown = BA_BOOLEAN_FALSE;

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
    
    SBR_cURL_LoopInitialize(NULL);
    
    sbrMainLoopDisconnected = BA_BOOLEAN_FALSE;
    
    while (!SBR_MainLoop_IsShuttingDown()) {
        size_t receivedBytes;
        const struct curl_ws_frame* metadata;
        size_t currentBufferSize = sizeof(char) * (bufferSize + 1);
        char* buffer = BA_Memory_Allocate(currentBufferSize, SBR_MEMORY_TYPE_EVENT_BUFFER);
        // FIXME: On release builds, Discord would randomly disconnect us. Figure out why
        
        if (!SBR_cURL_WebSocketReceive(buffer, bufferSize, &receivedBytes, &metadata)) {
            BA_Memory_Deallocate(buffer, currentBufferSize, SBR_MEMORY_TYPE_EVENT_BUFFER);
            
            if (sbrMainLoopDisconnected)
                break;

            continue;
        }

        buffer[receivedBytes] = '\0';

        if (metadata->bytesleft != 0) {
            BA_LOGGER_WARN("Buffer ran out of space\n");

            BA_Boolean disconnected = BA_BOOLEAN_FALSE;
            
            while (metadata->bytesleft != 0) {
                char* temporaryBuffer = malloc(sizeof(char) * (bufferSize + 1));
                size_t temporaryReceivedBytes;

                if (SBR_cURL_WebSocketReceive(&temporaryBuffer, bufferSize, &temporaryReceivedBytes, &metadata)) {
                    temporaryBuffer[bufferSize + 1] = '\0';

                    currentBufferSize += bufferSize + 1;
                    BA_Memory_AddSize(bufferSize + 1, SBR_MEMORY_TYPE_EVENT_BUFFER);
                    BA_String_Append(&buffer, temporaryBuffer);
                    free(temporaryBuffer);
                    continue;
                }

                BA_Memory_Deallocate(buffer, currentBufferSize, SBR_MEMORY_TYPE_EVENT_BUFFER);
                free(temporaryBuffer);
                
                disconnected = BA_BOOLEAN_TRUE;
                
                break;
            }

            if (disconnected)
                break;
        }

        if (BA_BITWISE_IS_BIT_SET(metadata->flags, CURLWS_CLOSE)) {
            uint16_t code = 0;
            char* message = malloc(sizeof(char*) * (receivedBytes - sizeof(uint16_t)));

            memcpy(&code, buffer, sizeof(uint16_t));
            memcpy(&message, buffer + sizeof(uint16_t), sizeof(char) * receivedBytes);
            
            code = ntohs(code);

            SBR_Gateway_ParseError(code, message);
            BA_Memory_Deallocate(buffer, currentBufferSize, SBR_MEMORY_TYPE_EVENT_BUFFER);
            free(message);

            if (!SBR_GatewayError_CanReconnect(code) || sbrMainLoopDisconnected) { // HACK: For invalidated session
                BA_LOGGER_INFO("Cannot reconnect, restarting bot\n");
                SBR_MainLoop_SignalDisconnected();
                break;
            }

            SBR_Gateway_AttemptReconnect();
            continue;
        }
        
        SBR_Gateway_Parse(buffer);
        BA_Memory_Deallocate(buffer, currentBufferSize, SBR_MEMORY_TYPE_EVENT_BUFFER);
    }

    SBR_cURL_Close(BA_BOOLEAN_TRUE);
    SBR_SupportChannels_Deallocate();
    SBR_Bot_Set(NULL);
    return !sbrMainLoopDisconnected;
#else
    BA_LOGGER_WARN("You're not supposed to call this\n");
    return BA_BOOLEAN_TRUE;
#endif
}

void SBR_MainLoop_SignalDisconnected(void) {
    sbrMainLoopDisconnected = BA_BOOLEAN_TRUE;
}

void SBR_MainLoop_Shutdown(void) {
    sbrMainLoopShuttingDown = BA_BOOLEAN_TRUE;
}

BA_Boolean SBR_MainLoop_IsShuttingDown(void) {
    return sbrMainLoopShuttingDown;
}
