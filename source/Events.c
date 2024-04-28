// Copyright (c) 2024, PortalPlayer <email@portalplayer.xyz>
// Licensed under MIT <https://opensource.org/licenses/MIT>

#include <BaconAPI/Logger.h>

#include "Events.h"

#define SBR_EVENTS_SETUP_EVENT_FUNCTIONS(name, ...) \
static SBR_Events_ ## name ## Action sbrEvents ## name = NULL; \
void SBR_Events_Set ## name ## Action(SBR_Events_ ## name ## Action action) { \
    sbrEvents ## name = action;                     \
}                                                   \
void SBR_Events_ ## name(__VA_ARGS__) {             \
    BA_LOGGER_TRACE("Calling custom event: " #name "\n"); \
    if (sbrEvents ## name == NULL) {                \
        BA_LOGGER_TRACE("Custom event function is null\n"); \
        return;                                     \
    }                                               \
    sbrEvents ## name

SBR_EVENTS_SETUP_EVENT_FUNCTIONS(MessageSent, SBR_DiscordMessage* message)(message);}
SBR_EVENTS_SETUP_EVENT_FUNCTIONS(Ready)();}
