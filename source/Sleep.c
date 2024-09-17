// Copyright (c) 2024, PortalPlayer <email@portalplayer.xyz>
// Licensed under MIT <https://opensource.org/licenses/MIT>

#include <BaconAPI/OperatingSystem.h>

#if BA_OPERATINGSYSTEM_POSIX_COMPLIANT
#   include <time.h>
#elif BA_OPERATINGSYSTEM_WINDOWS
#   include <Windows.h>
#endif

#include "Sleep.h"

void SBR_Sleep(int milliseconds) {
#if BA_OPERATINGSYSTEM_POSIX_COMPLIANT
    struct timespec time;

    time.tv_sec = milliseconds / 1000;
    time.tv_nsec = milliseconds % 1000 * 1000000;

    nanosleep(&time, NULL);
#elif BA_OPERATINGSYSTEM_WINDOWS
    Sleep(milliseconds);
#endif
}
