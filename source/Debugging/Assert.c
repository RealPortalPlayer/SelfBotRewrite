// Copyright (c) 2024, PortalPlayer <email@portalplayer.xyz>
// Licensed under MIT <https://opensource.org/licenses/MIT>

#include "Debugging/Assert.h"

#include <string.h>
#include <BaconAPI/String.h>

static const char* sbrAssertCode = NULL;
static char* sbrAssertMessage = NULL;

const char* SBR_Assert_GetCode(void) {
    return sbrAssertCode;
}

const char* SBR_Assert_GetMessage(void) {
    return sbrAssertMessage;
}

void SBR_Assert_Set(const char* code, const char* message, ...) {
    sbrAssertCode = code;

    if (sbrAssertMessage != NULL)
        free(sbrAssertMessage);

    sbrAssertMessage = BA_String_Copy(message);

    va_list arguments;

    va_start(arguments, message);
    BA_String_FormatPremadeList(&sbrAssertMessage, arguments);
    va_end(arguments);

    size_t sbrAssertMessageLength = strlen(sbrAssertMessage);

    if (sbrAssertMessage[sbrAssertMessageLength - 1] != '\n')
        return;

    sbrAssertMessage[sbrAssertMessageLength - 1] = '\0';
}
