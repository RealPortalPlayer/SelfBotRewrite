// Purpose: Bot events
// Created on: 4/28/24 @ 10:36 AM

// Copyright (c) 2024, PortalPlayer <email@portalplayer.xyz>
// Licensed under MIT <https://opensource.org/licenses/MIT>

#pragma once

#include "Discord/Objects/Message.h"

#define SBR_EVENTS_SETUP_EVENT(name, ...) \
typedef void (*SBR_Events_ ## name ## Action)(__VA_ARGS__); \
void SBR_Events_ ## name(__VA_ARGS__); \
void SBR_Events_Set ## name ## Action(SBR_Events_ ## name ## Action action)

SBR_EVENTS_SETUP_EVENT(MessageSent, SBR_DiscordMessage* message);
SBR_EVENTS_SETUP_EVENT(Ready, void);
