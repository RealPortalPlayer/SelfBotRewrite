// Copyright (c) 2024, PortalPlayer <email@portalplayer.xyz>
// Licensed under MIT <https://opensource.org/licenses/MIT>

#include <string.h>
#include <BaconAPI/ArgumentHandler.h>
#include <Time.h>
#include <BaconAPI/Debugging/Assert.h>
#include <BaconAPI/Logger.h>

int main(int argc, char** argv) {
    BA_ArgumentHandler_Initialize(argc, argv);

    SBR_Time* parsedTime = SBR_Time_Parse("2015-04-26T06:26:56.936000+00:00");
    const char* monthName = SBR_Time_GetMonthName(parsedTime);
    
    BA_LOGGER_INFO("Time: (%s) %i/%i/%i @ %i:%i:%i.%i\n", monthName, parsedTime->month, parsedTime->day, parsedTime->year, parsedTime->hour, parsedTime->minute, parsedTime->second, parsedTime->millisecond);
    BA_ASSERT(parsedTime->year == 2015, "Wrong year\n");
    BA_ASSERT(parsedTime->month == 4, "Wrong month\n");
    BA_ASSERT(parsedTime->day == 26, "Wrong day\n");
    BA_ASSERT(parsedTime->hour == 6, "Wrong hour\n");
    BA_ASSERT(parsedTime->minute == 26, "Wrong minute\n");
    BA_ASSERT(parsedTime->second == 56, "Wrong second\n");
    BA_ASSERT(parsedTime->millisecond == 936000, "Wrong milliseconds");
    BA_ASSERT(strcmp(monthName, "April") == 0, "Wrong month name");
}