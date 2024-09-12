// Copyright (c) 2024, PortalPlayer <email@portalplayer.xyz>
// Licensed under MIT <https://opensource.org/licenses/MIT>

#include <stdlib.h>

#include "ISOTime.h"
#include "Memory.h"

static char* sbrTimeMonthNames[] = {
    "January", "February", "March",
    "April", "May", "June",
    "July", "August", "September",
    "October", "November", "December"
};

static char* sbrTimeDayNames[] = {
    "Sunday", "Monday", "Tuesday",
    "Wednesday", "Thursday", "Friday",
    "Saturday"
};

struct tm* SBR_Time_Parse(const char* string) {
    if (string == NULL)
        return NULL;

    struct tm* time = BA_Memory_Allocate(sizeof(struct tm), SBR_MEMORY_TYPE_TIME);

    sscanf(string, "%d-%d-%dT%d:%d:%dZ", &time->tm_year, &time->tm_mon, &time->tm_mday, &time->tm_hour, &time->tm_min, &time->tm_sec);

    time->tm_year -= 1900;
    time->tm_mon -= 1;

    mktime(time);
    return time;
}

const char* SBR_Time_GetMonthName(const struct tm* time) {
    return sbrTimeMonthNames[time->tm_mon * (time->tm_mon < 0 ? -1 : 1) % 12];
}

const char* SBR_Time_GetDayName(const struct tm* time) {
    return sbrTimeDayNames[time->tm_wday * (time->tm_wday < 0 ? -1 : 1) % 7];
}

void SBR_Time_Deallocate(struct tm* time) {
    if (time == NULL)
        return;
    
    BA_Memory_Deallocate(time, sizeof(struct tm), SBR_MEMORY_TYPE_TIME);
}
