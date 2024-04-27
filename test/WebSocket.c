// Copyright (c) 2024, PortalPlayer <email@portalplayer.xyz>
// Licensed under MIT <https://opensource.org/licenses/MIT>

#include <BaconAPI/ArgumentHandler.h>
#include <cURL.h>
#include <string.h>

int main(int argc, char** argv) {
    BA_ArgumentHandler_Initialize(argc, argv);
    
    const char* message = "Test";

    if (argc >= 2)
        message = argv[1];

    BA_LOGGER_INFO("Initializing curl\n");
    SBR_cURL_Initialize("ws://127.0.0.1:1234");
    BA_LOGGER_INFO("Sending: %s\n", message);

    if (SBR_cURL_WebSocketSend(message, strlen(message), NULL, CURLWS_TEXT)) {
        BA_LOGGER_INFO("Waiting for response\n");

        while (BA_BOOLEAN_TRUE) {
            size_t bufferSize = 1024;
            char buffer[bufferSize];
            size_t receivedBytes;
            const struct curl_ws_frame* metadata;
        
            if (!SBR_cURL_WebSocketReceive(buffer, bufferSize, &receivedBytes, &metadata))
                continue;

            BA_LOGGER_INFO("Got response: ");

            for (size_t i = 0; i < receivedBytes; i++)
                BA_Logger_LogImplementation(BA_BOOLEAN_FALSE, BA_LOGGER_LOG_LEVEL_INFO, "%c", buffer[i]);

            BA_Logger_LogImplementation(BA_BOOLEAN_FALSE, BA_LOGGER_LOG_LEVEL_INFO, "\n");
            break;
        }
    }
    
    BA_LOGGER_INFO("Closing cURL\n");
    SBR_cURL_Close(BA_BOOLEAN_TRUE);
}