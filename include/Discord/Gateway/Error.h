// Purpose: Gateway error codes
// Created on: 4/24/24 @ 1:38 PM

// Copyright (c) 2024, PortalPlayer <email@portalplayer.xyz>
// Licensed under MIT <https://opensource.org/licenses/MIT>

#pragma once

#include <BaconAPI/Internal/Boolean.h>

typedef enum {
    /**
     * An unknown error occurred
     * @note Can/should reconnect
     */
    SBR_GATEWAYERROR_CODE_UNKNOWN = 4000,

    /**
     * Unknown operation code
     * @note Can reconnect
     */
    SBR_GATEWAYERROR_CODE_UNKNOWN_OPERATION_CODE,

    /**
     * Invalid payload
     * @note Can reconnect
     */
    SBR_GATEWAYERROR_CODE_DECODE_ERROR,

    /**
     * Sent payload before identifying
     * @note Can reconnect
     */
    SBR_GATEWAYERROR_CODE_NOT_AUTHENTICATED,

     /**
     * Invalid token
     * @note Can't reconnect
     */
    SBR_GATEWAYERROR_CODE_AUTHENTICATION_FAILED,

     /**
     * Sent more than one identify payload
     * @note Can reconnect
     */
    SBR_GATEWAYERROR_CODE_ALREADY_AUTHENTICATED,

     /**
     * Sequence invalid while resuming
     * @note Can/should reconnect, and start new session
     */
    SBR_GATEWAYERROR_CODE_INVALID_SEQUENCE = 4007,

     /**
     * Sending payloads too quickly
     * @note Can/should reconnect, and start new session
     */
    SBR_GATEWAYERROR_CODE_RATE_LIMITED,

     /**
     * Took too long to send a heartbeat
     * @note Can/should reconnect, and start new session
     */
    SBR_GATEWAYERROR_CODE_SESSION_TIMED_OUT,

     /**
     * @note Can't reconnect
     */
    SBR_GATEWAYERROR_CODE_INVALID_SHARD,

     /**
     * Too many guilds
     * @note Can't reconnect
     */
    SBR_GATEWAYERROR_CODE_SHARDING_REQUIRED,

     /**
     * Invalid or discontinued API version
     * @note Can't reconnect
     */
    SBR_GATEWAYERROR_CODE_INVALID_API_VERSION,

     /**
     * @note Can't reconnect
     */
    SBR_GATEWAYERROR_CODE_INVALID_INTENTS,

     /**
     * Intent is either not enabled on the dashboard, or Discord restricted it for the bot
     * @note Can't reconnect
     */
    SBR_GATEWAYERROR_CODE_DISALLOWED_INTENTS,

    /**
     * Invalid User Agent, or Cloudflare doesn't like us
     */
    SBR_GATEWAYERROR_CODE_UNOFFICIAL_CLOUDFLARE = 40333,
 
    /**
     * Not a real code
     */
    SBR_GATEWAYERROR_CODE_SIZE
} SBR_GatewayError_Codes;

BA_Boolean SBR_GatewayError_CanReconnect(SBR_GatewayError_Codes code);
BA_Boolean SBR_GatewayError_ShouldReconnect(SBR_GatewayError_Codes code);
BA_Boolean SBR_GatewayError_IsFatal(SBR_GatewayError_Codes code);
BA_Boolean SBR_GatewayError_IsValid(SBR_GatewayError_Codes code);
