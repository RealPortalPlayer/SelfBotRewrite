// Copyright (c) 2024, PortalPlayer <email@portalplayer.xyz>
// Licensed under MIT <https://opensource.org/licenses/MIT>

#include <BaconAPI/ArgumentHandler.h>
#include <WebSocket/cURL.h>
#include <Discord/Gateway/Event.h>

int main(int argc, char** argv) {
    BA_ArgumentHandler_Initialize(argc, argv);
    BA_LOGGER_INFO("Initializing curl\n");
    SBR_cURL_Initialize("ws://127.0.0.1:1234");
    BA_LOGGER_INFO("Sending Gateway event\n");
    BA_ASSERT(SBR_GatewayEvent_Send(SBR_GatewayEvent_Create(SBR_GATEWAYEVENT_CODE_HEARTBEAT, 0, "")), "Failed to send Gateway event. Code is receive only?\n");
}
