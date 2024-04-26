// Copyright (c) 2024, PortalPlayer <email@portalplayer.xyz>
// Licensed under MIT <https://opensource.org/licenses/MIT>

#include <BaconAPI/String.h>
#include <curl/curl.h>

#include "UserAgent.h"


const char* SBR_UserAgent_Get(void) {
    static char* userAgent = NULL;

    if (userAgent == NULL) {
        userAgent = BA_String_Copy("SelfBotRewrite/" SRB_VERSION " ");

        BA_String_Append(&userAgent, curl_version());
    }

    return userAgent;
}
