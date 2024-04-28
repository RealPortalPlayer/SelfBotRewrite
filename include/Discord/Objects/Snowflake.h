// Purpose: Implementation of snowflakes: Discords ID system
// Created on: 4/24/24 @ 12:09 PM

// Copyright (c) 2024, PortalPlayer <email@portalplayer.xyz>
// Licensed under MIT <https://opensource.org/licenses/MIT>

#pragma once

#include <inttypes.h>

typedef struct {
    /**
     * Milliseconds since around 2015
     */
    uint64_t timestamp;

    uint8_t workerId;
    uint8_t processId;

    /**
     * Increments with every ID generated on the same process
     */
    uint32_t increment;
} SBR_Snowflake;

SBR_Snowflake* SBR_Snowflake_ConvertFromNumber(uint64_t number);
uint64_t SBR_Snowflake_ConvertToNumber(const SBR_Snowflake* snowflake);
uint64_t SBR_Snowflake_Create(uint64_t timestamp, uint8_t workerId, uint8_t processId, uint32_t increment);

#define SBR_SNOWFLAKE_EPOCH 1420070400000
