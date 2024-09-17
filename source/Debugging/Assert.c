// Copyright (c) 2024, PortalPlayer <email@portalplayer.xyz>
// Licensed under MIT <https://opensource.org/licenses/MIT>

#include "Debugging/Assert.h"

#include <string.h>
#include <BaconAPI/String.h>

static const char* sbrAssertFileName = NULL;
static int sbrAssertLineNumber = 0;
static const char* sbrAssertFunctionName = NULL;
static const char* sbrAssertCode = NULL;
static char* sbrAssertMessage = NULL;

const char* SBR_Assert_GetFileName(void) {
    return sbrAssertFileName;
}

int SBR_Assert_GetLineNumber(void) {
    return sbrAssertLineNumber;
}

const char* SBR_Assert_GetFunctionName(void) {
    return sbrAssertFunctionName;
}

const char* SBR_Assert_GetCode(void) {
    return sbrAssertCode;
}

const char* SBR_Assert_GetMessage(void) {
    return sbrAssertMessage;
}

void SBR_Assert_Set(const char* fileName, int lineNumber, const char* functionName, const char* code, const char* message, ...) {
    SBR_Assert_Reset();

    sbrAssertFileName = fileName;
    sbrAssertLineNumber = lineNumber;
    sbrAssertFunctionName = functionName;
    sbrAssertCode = code;

    va_list arguments;

    va_start(arguments, message);
    
    sbrAssertMessage = BA_String_FormatPremadeList(BA_String_Copy(message), arguments);

    va_end(arguments);

    size_t sbrAssertMessageLength = strlen(sbrAssertMessage);

    if (sbrAssertMessage[sbrAssertMessageLength - 1] != '\n')
        return;

    sbrAssertMessage[sbrAssertMessageLength - 1] = '\0';
}

void SBR_Assert_Reset(void) {
    sbrAssertFileName = NULL;
    sbrAssertLineNumber = 0;
    sbrAssertFunctionName = NULL;
    sbrAssertCode = NULL;

    if (sbrAssertMessage == NULL)
        return;

    free(sbrAssertMessage);

    sbrAssertMessage = NULL;
}
