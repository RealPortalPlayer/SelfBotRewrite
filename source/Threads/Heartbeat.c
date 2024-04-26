// Copyright (c) 2024, PortalPlayer <email@portalplayer.xyz>
// Licensed under MIT <https://opensource.org/licenses/MIT>

#include <BaconAPI/Thread.h>
#include <BaconAPI/Debugging/Assert.h>
#include <BaconAPI/Internal/OperatingSystem.h>

#if BA_OPERATINGSYSTEM_POSIX_COMPLIANT
#   include <unistd.h>
#elif BA_OPERATINGSYSTEM_WINDOWS
#   include <Windows.h>
#endif

#include "Threads/Heartbeat.h"
#include "Discord/Gateway/Event.h"
#include "Discord/Gateway/Events.h"
#include "Discord/Gateway/Gateway.h"

static BA_Boolean sbrHeartbeatThreadPaused = BA_BOOLEAN_TRUE;

SBR_THREADINTERNAL_CODE(Heartbeat, "heartbeat") {
    BA_LOGGER_DEBUG("Hello, from heartbeat thread\n");
    
    while (sbrHeartbeatInitialized) {
        if (sbrHeartbeatThreadPaused)
            continue;

        SBR_GATEWAY_SEND_AND_FREE(SBR_GatewayEvents_CreateHeartbeat());
        sleep(SBR_Gateway_GetInterval() / 1000);
    }

    return NULL;
}

void SBR_HeartbeatThread_Pause(BA_Boolean pause) {
    BA_LOGGER_TRACE("%s heartbeat thread\n", pause ? "Pausing" : "Unpausing");

    sbrHeartbeatThreadPaused = pause;
}
