// Copyright (c) 2024, PortalPlayer <email@portalplayer.xyz>
// Licensed under MIT <https://opensource.org/licenses/MIT>

#include <stdlib.h>
#include <BaconAPI/Debugging/Assert.h>

#include "Time.h"

SBR_Time* SBR_Time_Parse(const char* string) {
    SBR_Time* time = malloc(sizeof(SBR_Time));

    BA_ASSERT(time != NULL, "Failed to allocate memory for time\n");
    sscanf(string, "%d-%d-%dT%d:%d:%fZ", &time->year, &time->month, &time->day, &time->hour, &time->minute, &time->second);
    return time;
}
