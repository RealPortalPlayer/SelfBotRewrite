// Copyright (c) 2024, PortalPlayer <email@portalplayer.xyz>
// Licensed under MIT <https://opensource.org/licenses/MIT>

#include <stddef.h>

#include "Discord/Gateway/Error.h"
#include "Discord/Gateway/Errors.h"

BA_Boolean SBR_GatewayError_CanReconnect(SBR_GatewayError_Codes code) {
    return SBR_GatewayErrors_Get(code) != NULL;
}

BA_Boolean SBR_GatewayError_IsValid(SBR_GatewayError_Codes code) {
    return code < SBR_GATEWAYERROR_CODE_SIZE && code != 4006;
}
