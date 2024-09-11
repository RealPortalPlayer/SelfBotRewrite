// Copyright (c) 2024, PortalPlayer <email@portalplayer.xyz>
// Licensed under MIT <https://opensource.org/licenses/MIT>

#include "Prefix.h"
#include "Settings.h"
#include "Debugging/Assert.h"

const char* SBR_Prefix_Get(void) {
    static char* prefix = NULL;

    if (prefix == NULL)
        SBR_ASSERT(SBR_Settings_Get(SBR_Settings_IsDevelopmentMode() ? "DEVELOPMENT_PREFIX" : "PRODUCTION_PREFIX", &prefix, BA_BOOLEAN_FALSE), "Failed to find prefix\n");

    return prefix;
}
