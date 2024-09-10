// Copyright (c) 2024, PortalPlayer <email@portalplayer.xyz>
// Licensed under MIT <https://opensource.org/licenses/MIT>

#include <string.h>
#include <BaconAPI/ArgumentHandler.h>
#include <Time.h>
#include <BaconAPI/Debugging/Assert.h>
#include <BaconAPI/Logger.h>

int main(int argc, char** argv) {
    BA_ArgumentHandler_Initialize(argc, argv);

    struct tm* parsedTime = SBR_Time_Parse("2015-04-26T06:26:56.936000+00:00");
    const char* monthName = SBR_Time_GetMonthName(parsedTime);
    
    BA_LOGGER_INFO("Time: (%s) %i/%i/%i @ %i:%i:%i\n", monthName, parsedTime->tm_mon + 1, parsedTime->tm_mday, parsedTime->tm_year + 1900, parsedTime->tm_hour - 1, parsedTime->tm_min, parsedTime->tm_sec);
    BA_ASSERT(parsedTime->tm_year == 115, "Wrong year\n");
    BA_ASSERT(parsedTime->tm_mon == 3, "Wrong month\n");
    BA_ASSERT(parsedTime->tm_mday == 26, "Wrong day\n");
    BA_ASSERT(parsedTime->tm_hour == 7, "Wrong hour\n");
    BA_ASSERT(parsedTime->tm_min == 26, "Wrong minute\n");
    BA_ASSERT(parsedTime->tm_sec == 56, "Wrong second\n");
    BA_ASSERT(strcmp(monthName, "April") == 0, "Wrong month name\n");
}