// Copyright (c) 2024, PortalPlayer <email@portalplayer.xyz>
// Licensed under MIT <https://opensource.org/licenses/MIT>

#include "Discord/Gateway/Error.h"

BA_Boolean SBR_GatewayError_CanReconnect(SBR_GatewayError_Codes code) {
    return (code >= SBR_GATEWAYERROR_CODE_UNKNOWN && code <= SBR_GATEWAYERROR_CODE_NOT_AUTHENTICATED) ||
           (code >= SBR_GATEWAYERROR_CODE_ALREADY_AUTHENTICATED && code <= SBR_GATEWAYERROR_CODE_SESSION_TIMED_OUT);
}

BA_Boolean SBR_GatewayError_ShouldReconnect(SBR_GatewayError_Codes code) {
    return code == SBR_GATEWAYERROR_CODE_UNKNOWN ||
           (code >= SBR_GATEWAYERROR_CODE_INVALID_SEQUENCE && code <= SBR_GATEWAYERROR_CODE_SESSION_TIMED_OUT);
}

BA_Boolean SBR_GatewayError_IsFatal(SBR_GatewayError_Codes code) {
    return code == SBR_GATEWAYERROR_CODE_AUTHENTICATION_FAILED ||
           (code >= SBR_GATEWAYERROR_CODE_INVALID_SHARD && code <= SBR_GATEWAYERROR_CODE_DISALLOWED_INTENTS);
}

BA_Boolean SBR_GatewayError_IsValid(SBR_GatewayError_Codes code) {
    return code < SBR_GATEWAYERROR_CODE_SIZE && code != 4006;
}
