// Copyright (c) 2024, PortalPlayer <email@portalplayer.xyz>
// Licensed under MIT <https://opensource.org/licenses/MIT>

#include <BaconAPI/Debugging/StaticAssert.h>
#include <BaconAPI/Logger.h>

#include "Discord/Gateway/Errors.h"
#include "Debugging/Assert.h"

#define SBR_GATEWAYERRORS_CREATE_ERROR_FUNCTION_HEADER(name) static void SBR_GatewayErrors_Action ## name(const char* message)

SBR_GATEWAYERRORS_CREATE_ERROR_FUNCTION_HEADER(SBR_GATEWAYERROR_CODE_UNKNOWN);
SBR_GATEWAYERRORS_CREATE_ERROR_FUNCTION_HEADER(SBR_GATEWAYERROR_CODE_UNKNOWN_OPERATION_CODE);
SBR_GATEWAYERRORS_CREATE_ERROR_FUNCTION_HEADER(SBR_GATEWAYERROR_CODE_DECODE_ERROR);
SBR_GATEWAYERRORS_CREATE_ERROR_FUNCTION_HEADER(SBR_GATEWAYERROR_CODE_NOT_AUTHENTICATED);
SBR_GATEWAYERRORS_CREATE_ERROR_FUNCTION_HEADER(SBR_GATEWAYERROR_CODE_AUTHENTICATION_FAILED);
SBR_GATEWAYERRORS_CREATE_ERROR_FUNCTION_HEADER(SBR_GATEWAYERROR_CODE_ALREADY_AUTHENTICATED);
SBR_GATEWAYERRORS_CREATE_ERROR_FUNCTION_HEADER(SBR_GATEWAYERROR_CODE_INVALID_SEQUENCE);
SBR_GATEWAYERRORS_CREATE_ERROR_FUNCTION_HEADER(SBR_GATEWAYERROR_CODE_RATE_LIMITED);
SBR_GATEWAYERRORS_CREATE_ERROR_FUNCTION_HEADER(SBR_GATEWAYERROR_CODE_SESSION_TIMED_OUT);
SBR_GATEWAYERRORS_CREATE_ERROR_FUNCTION_HEADER(SBR_GATEWAYERROR_CODE_INVALID_SHARD);
SBR_GATEWAYERRORS_CREATE_ERROR_FUNCTION_HEADER(SBR_GATEWAYERROR_CODE_SHARDING_REQUIRED);
SBR_GATEWAYERRORS_CREATE_ERROR_FUNCTION_HEADER(SBR_GATEWAYERROR_CODE_INVALID_API_VERSION);
SBR_GATEWAYERRORS_CREATE_ERROR_FUNCTION_HEADER(SBR_GATEWAYERROR_CODE_INVALID_INTENTS);
SBR_GATEWAYERRORS_CREATE_ERROR_FUNCTION_HEADER(SBR_GATEWAYERROR_CODE_DISALLOWED_INTENTS);

#define SBR_GATEWAYERRORS_CREATE_ENTRY(code, reconnectable) \
{                                                           \
    code,                                                   \
    reconnectable,                                          \
    SBR_GatewayErrors_Action ## code                        \
}

#define SBR_GATEWAYERRORS_STUB_ENTRY {0, BA_BOOLEAN_FALSE, NULL}

static SBR_GatewayErrors_Information sbrGatewayErrors[] = {
    SBR_GATEWAYERRORS_CREATE_ENTRY(SBR_GATEWAYERROR_CODE_UNKNOWN, BA_BOOLEAN_TRUE),
    SBR_GATEWAYERRORS_CREATE_ENTRY(SBR_GATEWAYERROR_CODE_UNKNOWN_OPERATION_CODE, BA_BOOLEAN_TRUE),
    SBR_GATEWAYERRORS_CREATE_ENTRY(SBR_GATEWAYERROR_CODE_DECODE_ERROR, BA_BOOLEAN_TRUE),
    SBR_GATEWAYERRORS_CREATE_ENTRY(SBR_GATEWAYERROR_CODE_NOT_AUTHENTICATED, BA_BOOLEAN_TRUE),
    SBR_GATEWAYERRORS_CREATE_ENTRY(SBR_GATEWAYERROR_CODE_AUTHENTICATION_FAILED, BA_BOOLEAN_FALSE),
    SBR_GATEWAYERRORS_CREATE_ENTRY(SBR_GATEWAYERROR_CODE_ALREADY_AUTHENTICATED, BA_BOOLEAN_TRUE),
    SBR_GATEWAYERRORS_STUB_ENTRY,
    SBR_GATEWAYERRORS_CREATE_ENTRY(SBR_GATEWAYERROR_CODE_INVALID_SEQUENCE, BA_BOOLEAN_TRUE),
    SBR_GATEWAYERRORS_CREATE_ENTRY(SBR_GATEWAYERROR_CODE_RATE_LIMITED, BA_BOOLEAN_TRUE),
    SBR_GATEWAYERRORS_CREATE_ENTRY(SBR_GATEWAYERROR_CODE_SESSION_TIMED_OUT, BA_BOOLEAN_TRUE),
    SBR_GATEWAYERRORS_CREATE_ENTRY(SBR_GATEWAYERROR_CODE_INVALID_SHARD, BA_BOOLEAN_FALSE),
    SBR_GATEWAYERRORS_CREATE_ENTRY(SBR_GATEWAYERROR_CODE_SHARDING_REQUIRED, BA_BOOLEAN_FALSE),
    SBR_GATEWAYERRORS_CREATE_ENTRY(SBR_GATEWAYERROR_CODE_INVALID_API_VERSION, BA_BOOLEAN_FALSE),
    SBR_GATEWAYERRORS_CREATE_ENTRY(SBR_GATEWAYERROR_CODE_INVALID_INTENTS, BA_BOOLEAN_FALSE),
    SBR_GATEWAYERRORS_CREATE_ENTRY(SBR_GATEWAYERROR_CODE_DISALLOWED_INTENTS, BA_BOOLEAN_FALSE)
};

BA_STATIC_ASSERT_LOOKUP_TABLE_CHECK(sbrGatewayErrors, SBR_GATEWAYERROR_CODE_SIZE - 4000);

const SBR_GatewayErrors_Information* SBR_GatewayErrors_Get(SBR_GatewayError_Codes code) {
    for (int index = 0; index < SBR_GATEWAYERROR_CODE_SIZE - 4000; index++) {
        if (sbrGatewayErrors[index].code != code)
            continue;

        return &sbrGatewayErrors[index];
    }

    return NULL;
}

SBR_GATEWAYERRORS_CREATE_ERROR_FUNCTION_HEADER(SBR_GATEWAYERROR_CODE_UNKNOWN) {
    BA_LOGGER_ERROR("Unknown Discord Gateway error: %s\n", message);
}

SBR_GATEWAYERRORS_CREATE_ERROR_FUNCTION_HEADER(SBR_GATEWAYERROR_CODE_UNKNOWN_OPERATION_CODE) {
    BA_LOGGER_ERROR("Invalid operation code: %s\n", message);
}

SBR_GATEWAYERRORS_CREATE_ERROR_FUNCTION_HEADER(SBR_GATEWAYERROR_CODE_DECODE_ERROR) {
    BA_LOGGER_ERROR("Invalid payload: %s\n", message);
}

SBR_GATEWAYERRORS_CREATE_ERROR_FUNCTION_HEADER(SBR_GATEWAYERROR_CODE_NOT_AUTHENTICATED) {
    BA_LOGGER_ERROR("Not authenticated: %s\n", message);
}

SBR_GATEWAYERRORS_CREATE_ERROR_FUNCTION_HEADER(SBR_GATEWAYERROR_CODE_AUTHENTICATION_FAILED) {
    SBR_ASSERT_ALWAYS("Invalid token\n");
}

SBR_GATEWAYERRORS_CREATE_ERROR_FUNCTION_HEADER(SBR_GATEWAYERROR_CODE_ALREADY_AUTHENTICATED) {
    BA_LOGGER_ERROR("Already authenticated\n");
}

SBR_GATEWAYERRORS_CREATE_ERROR_FUNCTION_HEADER(SBR_GATEWAYERROR_CODE_INVALID_SEQUENCE) {
    BA_LOGGER_ERROR("Invalid sequence: %s\n", message);
}

SBR_GATEWAYERRORS_CREATE_ERROR_FUNCTION_HEADER(SBR_GATEWAYERROR_CODE_RATE_LIMITED) {
    BA_LOGGER_ERROR("We're rate-limited\n");
}

SBR_GATEWAYERRORS_CREATE_ERROR_FUNCTION_HEADER(SBR_GATEWAYERROR_CODE_SESSION_TIMED_OUT) {
    BA_LOGGER_ERROR("Session timed out (failed to send heartbeat)\n");
}

SBR_GATEWAYERRORS_CREATE_ERROR_FUNCTION_HEADER(SBR_GATEWAYERROR_CODE_INVALID_SHARD) {
    SBR_ASSERT_ALWAYS("Supplied shards are invalid: %s\n", message);
}

SBR_GATEWAYERRORS_CREATE_ERROR_FUNCTION_HEADER(SBR_GATEWAYERROR_CODE_SHARDING_REQUIRED) {
    SBR_ASSERT_ALWAYS("Bot requires sharding\n");
}

SBR_GATEWAYERRORS_CREATE_ERROR_FUNCTION_HEADER(SBR_GATEWAYERROR_CODE_INVALID_API_VERSION) {
    SBR_ASSERT_ALWAYS("API version is invalid (perhaps out-of-service?)\n");
}
SBR_GATEWAYERRORS_CREATE_ERROR_FUNCTION_HEADER(SBR_GATEWAYERROR_CODE_INVALID_INTENTS) {
    SBR_ASSERT_ALWAYS("Invalid intents: %s\n", message);
}

SBR_GATEWAYERRORS_CREATE_ERROR_FUNCTION_HEADER(SBR_GATEWAYERROR_CODE_DISALLOWED_INTENTS) {
    SBR_ASSERT_ALWAYS("Disallowed intents (either disabled or restricted): %s\n", message);
}
