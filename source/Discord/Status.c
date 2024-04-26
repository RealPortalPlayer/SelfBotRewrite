// Copyright (c) 2024, PortalPlayer <email@portalplayer.xyz>
// Licensed under MIT <https://opensource.org/licenses/MIT>

#include <BaconAPI/Logger.h>

#include "Discord/Status.h"

#include <BaconAPI/String.h>

const char* SBR_DiscordStatus_ToString(SBR_DiscordStatus status) {
    switch (status) {
        case SBR_DISCORDSTATUS_DO_NOT_DISTURB: return "dnd";
        case SBR_DISCORDSTATUS_IDLE: return "idle";
        case SBR_DISCORDSTATUS_INVISIBLE: return "invisible";
        default: BA_LOGGER_WARN("Invalid status: %i\n", status);
        case SBR_DISCORDSTATUS_ONLINE: return "online";
    }
}

SBR_DiscordStatus SBR_DiscordStatus_FromString(const char* status) {
    if (BA_String_Equals(status, "online", BA_BOOLEAN_TRUE))
        return SBR_DISCORDSTATUS_ONLINE;
    
    if (BA_String_Equals(status, "dnd", BA_BOOLEAN_TRUE))
        return SBR_DISCORDSTATUS_DO_NOT_DISTURB;

    if (BA_String_Equals(status, "idle", BA_BOOLEAN_TRUE))
        return SBR_DISCORDSTATUS_IDLE;

    if (BA_String_Equals(status, "invisible", BA_BOOLEAN_TRUE))
        return SBR_DISCORDSTATUS_INVISIBLE;

    BA_LOGGER_WARN("Invalid status: %s\n", status);
    return SBR_DISCORDSTATUS_ONLINE;
}
