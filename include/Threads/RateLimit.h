// Purpose: Rate-limit watchdogs
// Created on: 4/26/24 @ 11:15 AM

// Copyright (c) 2024, PortalPlayer <email@portalplayer.xyz>
// Licensed under MIT <https://opensource.org/licenses/MIT>

#pragma once

#include "ThreadInternal.h"

SBR_THREADINTERNAL_HEADER(RateLimitClearer);
SBR_THREADINTERNAL_HEADER(RateLimitDetecter);

BA_Boolean SBR_RateLimit_Sleeping(void);
