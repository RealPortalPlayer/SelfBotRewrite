// Copyright (c) 2024, PortalPlayer <email@portalplayer.xyz>
// Licensed under MIT <https://opensource.org/licenses/MIT>

#include <BaconAPI/Logger.h>

#include "Commands/Categories.h"
#include "Commands/Category.h"

void SBR_Categories_Register(void) {
    BA_LOGGER_INFO("Registering all categories\n");
    SBR_Category_Register("misc", "Commands that don't fit a specific category");
}
