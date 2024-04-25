// Purpose: Discord specific configuration
// Created on: 4/25/24 @ 12:51 PM

// Copyright (c) 2024, PortalPlayer <email@portalplayer.xyz>
// Licensed under MIT <https://opensource.org/licenses/MIT>

#pragma once

int SBR_DiscordConfiguration_GetAPIVersion(void);
const char* SBR_DiscordConfiguration_GetAPIRootURL(void);
const char* SBR_DiscordConfiguration_GetAPIURL(const char* path);
const char* SBR_DiscordConfiguration_GetWebSocketURL(void);
const char* SBR_DiscordConfiguration_GetCDNURL(const char* path);
