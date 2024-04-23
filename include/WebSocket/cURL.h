// Purpose: WebSocket wrapper around cURL
// Created on: 4/23/24 @ 4:17 PM


// Copyright (c) 2024, PortalPlayer <email@portalplayer.xyz>
// Licensed under MIT <https://opensource.org/licenses/MIT>

#pragma once

#include <curl/curl.h>

CURL* SBR_cURL_Get(void);

void SBR_cURL_Initialize(void);
