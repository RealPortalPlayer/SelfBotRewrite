// Copyright (c) 2024, PortalPlayer <email@portalplayer.xyz>
// Licensed under MIT <https://opensource.org/licenses/MIT>

#include "Discord/Gateway/Event.h"

BA_Boolean SBR_GatewayEvent_CanReceiveCode(SBR_GatewayEvent_Codes code) {
    return SBR_GatewayEvent_IsCodeValid(code) &&
           (code == SBR_GATEWAYEVENT_CODE_DISPATCH ||
           code == SBR_GATEWAYEVENT_CODE_HEARTBEAT ||
           code == SBR_GATEWAYEVENT_CODE_RECONNECT ||
           code >= SBR_GATEWAYEVENT_CODE_INVALID_SESSION);
}

BA_Boolean SBR_GatewayEvent_CanSendCode(SBR_GatewayEvent_Codes code) {
    return SBR_GatewayEvent_IsCodeValid(code) &&
           ((code >= SBR_GATEWAYEVENT_CODE_HEARTBEAT && code <= SBR_GATEWAYEVENT_CODE_RESUME) ||
           code == SBR_GATEWAYEVENT_CODE_REQUEST_GUILD_MEMBERS);
}

BA_Boolean SBR_GatewayEvent_IsCodeValid(SBR_GatewayEvent_Codes code) {
    return code < SBR_GATEWAYEVENT_CODE_SIZE && code != 5;
}
