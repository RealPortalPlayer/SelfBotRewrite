// Copyright (c) 2024, PortalPlayer <email@portalplayer.xyz>
// Licensed under MIT <https://opensource.org/licenses/MIT>

#include <BaconAPI/ArgumentHandler.h>
#include <BaconAPI/String.h>
#include <WebSocket/cURL.h>
#include <Discord/Gateway/Event.h>

int main(int argc, char** argv) {
    BA_ArgumentHandler_Initialize(argc, argv);
    BA_LOGGER_INFO("Initializing curl\n");
    SBR_cURL_Initialize("ws://127.0.0.1:1234");
    BA_LOGGER_INFO("Sending Gateway event\n");
    SBR_GatewayEvent_Send(SBR_GatewayEvent_Create(SBR_GATEWAYEVENT_CODE_HEARTBEAT, 0, ""));
    BA_LOGGER_INFO("Simulating response\n");

    {
        char* fakePacket = BA_String_Copy("{ \"op\": %i, \"d\": { } }");

        BA_ASSERT(fakePacket != NULL, "Failed to allocate memory for fake packet\n");
        BA_ASSERT(BA_String_Format(&fakePacket, SBR_GATEWAYEVENT_CODE_HEARTBEAT_ACKNOWLEDGE), "Failed to format fake packet\n");
        SBR_GatewayEvent_Parse(fakePacket);
    }
}
