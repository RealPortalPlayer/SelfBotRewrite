// Copyright (c) 2024, PortalPlayer <email@portalplayer.xyz>
// Licensed under MIT <https://opensource.org/licenses/MIT>

#include <stddef.h>
#include <BaconAPI/Debugging/Assert.h>

#include "Token.h"
#include "Settings.h"

const char* SBR_Token_Get(void) {
    static char* token = NULL;

    if (token == NULL)
        BA_ASSERT(SBR_Settings_Get(SBR_Settings_IsDevelopmentMode() ? "DEVELOPMENT_TOKEN" : "PRODUCTION_TOKEN", &token, BA_BOOLEAN_TRUE), "Cannot find token\n");
    
    return token;
}
