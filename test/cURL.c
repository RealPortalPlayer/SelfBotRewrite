// Copyright (c) 2024, PortalPlayer <email@portalplayer.xyz>
// Licensed under MIT <https://opensource.org/licenses/MIT>

#include <BaconAPI/ArgumentHandler.h>
#include <WebSocket/cURL.h>
#include <string.h>

int main(int argc, char** argv) {
    BA_ArgumentHandler_Initialize(argc, argv);
    
    const char* message = "Test";

    if (argc >= 2)
        message = argv[1];

    BA_LOGGER_INFO("Initializing curl\n");
    SBR_cURL_Initialize("ws://127.0.0.1:1234");
    BA_LOGGER_INFO("Sending: %s\n", message);
    SBR_CURL_ASSERT(SBR_cURL_Send(message, strlen(message), NULL, CURLWS_TEXT), "Failed to send message: %s\n");
}