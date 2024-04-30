// Copyright (c) 2024, PortalPlayer <email@portalplayer.xyz>
// Licensed under MIT <https://opensource.org/licenses/MIT>

#include <BaconAPI/Thread.h>
#include <BaconAPI/Debugging/Assert.h>
#include <BaconAPI/Internal/OperatingSystem.h>

#include "Threads/Heartbeat.h"
#include "Discord/Gateway/Event.h"
#include "Discord/Gateway/Events.h"
#include "Discord/Gateway/Gateway.h"
#include "Sleep.h"

static BA_Boolean sbrHeartbeatThreadPaused = BA_BOOLEAN_TRUE;

SBR_THREADINTERNAL_CODE(Heartbeat, "heartbeat", KILL) {
    static BA_Boolean first = BA_BOOLEAN_TRUE;
    
    BA_LOGGER_DEBUG("Hello, from heartbeat thread\n");
    
    while (sbrHeartbeatInitialized) {
        if (sbrHeartbeatThreadPaused)
            continue;

        if (first) {
            int jitter = rand() % 2 ? 1 : 0;

            BA_LOGGER_DEBUG("Jitter: %i\n", jitter);
            SBR_Sleep(SBR_Gateway_GetInterval() * jitter);

            first = BA_BOOLEAN_FALSE;
        }


        SBR_GATEWAY_SEND_AND_FREE(SBR_GatewayEvents_CreateHeartbeat());
        SBR_Sleep(SBR_Gateway_GetInterval());
    }

    return NULL;
}

void SBR_HeartbeatThread_Pause(BA_Boolean pause) {
    BA_LOGGER_TRACE("%s heartbeat thread\n", pause ? "Pausing" : "Unpausing");

    sbrHeartbeatThreadPaused = pause;
}
