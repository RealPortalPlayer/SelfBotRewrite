// Copyright (c) 2024, PortalPlayer <email@portalplayer.xyz>
// Licensed under MIT <https://opensource.org/licenses/MIT>

#include <BaconAPI/Thread.h>
#include <BaconAPI/OperatingSystem.h>

#if BA_OPERATINGSYSTEM_POSIX_COMPLIANT
#   include <unistd.h>
#elif BA_OPERATINGSYSTEM_WINDOWS
#   include <Windows.h>
#endif

#include "Threads/RateLimit.h"
#include "Discord/Gateway/Gateway.h"
#include "Sleep.h"

static volatile BA_Boolean sbrRateLimitSleeping;

SBR_THREADINTERNAL_CODE(RateLimitClearer, "rate-limit clearer", KILL) {
    BA_LOGGER_DEBUG("Hello, from rate-limit clearer\n");
    
    while (sbrRateLimitClearerInitialized) {
        SBR_Sleep(60000);
        SBR_Gateway_ResetRequestCount();
    }

    return NULL;
}

SBR_THREADINTERNAL_CODE(RateLimitDetecter, "rate-limit detecter", JOIN) {
    BA_LOGGER_DEBUG("Hello, from rate-limit detecter\n");

    while (sbrRateLimitDetecterInitialized) {
        if (SBR_Gateway_GetRequestCount() < 110)
            continue;

        BA_LOGGER_WARN("Rate-limit reached, sleeping for 60 seconds\n");

        sbrRateLimitSleeping = BA_BOOLEAN_TRUE;

        SBR_Sleep(60000);
        BA_LOGGER_TRACE("Rate-limit over\n");

        sbrRateLimitSleeping = BA_BOOLEAN_FALSE;
    }

    return NULL;
}

BA_Boolean SBR_RateLimit_Sleeping(void) {
    return sbrRateLimitSleeping;
}
