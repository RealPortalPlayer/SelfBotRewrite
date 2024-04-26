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

static BA_Boolean sbrHeartbeatThreadPaused = BA_BOOLEAN_TRUE;
static BA_Thread sbrHeartbeatThread;
static volatile BA_Boolean sbrHeartbeatInitialized = BA_BOOLEAN_FALSE;

static BA_THREAD_RETURN_VALUE BA_THREAD_ATTRIBUTE SBR_HeartbeatThread_Function(void* argument) {
    BA_LOGGER_DEBUG("Hello, from heartbeat thread\n");
    
    while (sbrHeartbeatInitialized) {
        if (sbrHeartbeatThreadPaused)
            continue;

        SBR_GatewayEvent_Send(SBR_GatewayEvents_CreateHeartbeat());
        sleep(SBR_GatewayEvent_GetInterval() / 1000);
    }

    return NULL;
}

void SBR_HeartbeatThread_Create(void) {
    BA_ASSERT(!sbrHeartbeatInitialized, "Already created heartbeat thread\n");

    sbrHeartbeatInitialized = BA_BOOLEAN_TRUE;

    BA_LOGGER_TRACE("Creating heartbeat thread\n");
    BA_ASSERT(BA_Thread_Create(&sbrHeartbeatThread, &SBR_HeartbeatThread_Function, NULL), "Failed to create heartbeat thread\n");
}

void SBR_HeartbeatThread_Pause(BA_Boolean pause) {
    BA_ASSERT(sbrHeartbeatInitialized, "Heartbeat thread not created\n");
    BA_LOGGER_TRACE("%s heartbeat thread\n", pause ? "Pausing" : "Unpausing");

    sbrHeartbeatThreadPaused = pause;
}

void SBR_HeartbeatThread_Destroy(void) {
    BA_ASSERT(sbrHeartbeatInitialized, "Heartbeat thread not created\n");
    BA_LOGGER_TRACE("Destroying heartbeat thread\n");

    sbrHeartbeatInitialized = BA_BOOLEAN_FALSE;
    
    SBR_HeartbeatThread_Pause(sbrHeartbeatThreadPaused);
    BA_ASSERT(BA_Thread_Join(sbrHeartbeatThread, NULL), "Failed to destroy heartbeat thread\n");
}
