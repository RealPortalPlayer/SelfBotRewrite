// Copyright (c) 2024, PortalPlayer <email@portalplayer.xyz>
// Licensed under MIT <https://opensource.org/licenses/MIT>

#include <BaconAPI/Internal/Boolean.h>
#include <BaconAPI/Debugging/Assert.h>

#include "WebSocket/cURL.h"

static CURL* sbrcURL;

CURL* SBR_cURL_Get(void) {
    return sbrcURL;
}

void SBR_cURL_Initialize(void) {
    static BA_Boolean intialized = BA_BOOLEAN_FALSE;

    BA_ASSERT(!intialized, "Already initialized cURL\n");

    intialized = BA_BOOLEAN_TRUE;

    BA_ASSERT((sbrcURL = curl_easy_init()), "Failed to initialize cURL\n");
}
