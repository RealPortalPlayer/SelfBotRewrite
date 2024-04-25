// Copyright (c) 2024, PortalPlayer <email@portalplayer.xyz>
// Licensed under MIT <https://opensource.org/licenses/MIT>

#include <BaconAPI/Math/Bitwise.h>

#include "Discord/Permissions.h"

BA_Boolean SBR_DiscordPermissions_Requires2FA(SBR_DiscordPermissions permission) {
    return BA_BITWISE_IS_BIT_SET(permission, SBR_DISCORDPERMISSION_KICK_MEMBERS) ||
           BA_BITWISE_IS_BIT_SET(permission, SBR_DISCORDPERMISSION_BAN_MEMBERS) ||
           BA_BITWISE_IS_BIT_SET(permission, SBR_DISCORDPERMISSION_ADMINISTRATOR) ||
           BA_BITWISE_IS_BIT_SET(permission, SBR_DISCORDPERMISSION_MANAGE_CHANNELS) ||
           BA_BITWISE_IS_BIT_SET(permission, SBR_DISCORDPERMISSION_MANAGE_GUILD) ||
           BA_BITWISE_IS_BIT_SET(permission, SBR_DISCORDPERMISSION_MANAGE_MESSAGES) ||
           BA_BITWISE_IS_BIT_SET(permission, SBR_DISCORDPERMISSION_MANAGE_ROLES) ||
           BA_BITWISE_IS_BIT_SET(permission, SBR_DISCORDPERMISSION_MANAGE_WEBHOOKS) ||
           BA_BITWISE_IS_BIT_SET(permission, SBR_DISCORDPERMISSION_MANAGE_GUILD_EXPRESSIONS) ||
           BA_BITWISE_IS_BIT_SET(permission, SBR_DISCORDPERMISSION_MANAGE_THREADS) ||
           BA_BITWISE_IS_BIT_SET(permission, SBR_DISCORDPERMISSION_VIEW_CREATOR_MONETIZATION_ANALYTICS);
}

BA_Boolean SBR_DiscordPermissions_IsTextChannelPermission(SBR_DiscordPermissions permission) {
    return BA_BITWISE_IS_BIT_SET(permission, SBR_DISCORDPERMISSION_CREATE_INSTANT_INVITE) ||
           BA_BITWISE_IS_BIT_SET(permission, SBR_DISCORDPERMISSION_MANAGE_CHANNELS) ||
           BA_BITWISE_IS_BIT_SET(permission, SBR_DISCORDPERMISSION_ADD_REACTIONS) ||
           BA_BITWISE_IS_BIT_SET(permission, SBR_DISCORDPERMISSION_VIEW_CHANNEL) ||
           BA_BITWISE_IS_BIT_SET(permission, SBR_DISCORDPERMISSION_SEND_MESSAGES) ||
           BA_BITWISE_IS_BIT_SET(permission, SBR_DISCORDPERMISSION_SEND_TTS_MESSAGES) ||
           BA_BITWISE_IS_BIT_SET(permission, SBR_DISCORDPERMISSION_MANAGE_MESSAGES) ||
           BA_BITWISE_IS_BIT_SET(permission, SBR_DISCORDPERMISSION_EMBED_LINKS) ||
           BA_BITWISE_IS_BIT_SET(permission, SBR_DISCORDPERMISSION_ATTACH_FILES) ||
           BA_BITWISE_IS_BIT_SET(permission, SBR_DISCORDPERMISSION_READ_MESSAGE_HISTORY) ||
           BA_BITWISE_IS_BIT_SET(permission, SBR_DISCORDPERMISSION_MENTION_EVERYONE) ||
           BA_BITWISE_IS_BIT_SET(permission, SBR_DISCORDPERMISSION_USE_EXTERNAL_EMOJIS) ||
           BA_BITWISE_IS_BIT_SET(permission, SBR_DISCORDPERMISSION_MANAGE_ROLES) ||
           BA_BITWISE_IS_BIT_SET(permission, SBR_DISCORDPERMISSION_MANAGE_WEBHOOKS) ||
           BA_BITWISE_IS_BIT_SET(permission, SBR_DISCORDPERMISSION_USE_APPLICATION_COMMANDS) ||
           BA_BITWISE_IS_BIT_SET(permission, SBR_DISCORDPERMISSION_MANAGE_THREADS) ||
           BA_BITWISE_IS_BIT_SET(permission, SBR_DISCORDPERMISSION_CREATE_PUBLIC_THREADS) ||
           BA_BITWISE_IS_BIT_SET(permission, SBR_DISCORDPERMISSION_CREATE_PRIVATE_THREADS) ||
           BA_BITWISE_IS_BIT_SET(permission, SBR_DISCORDPERMISSION_USE_EXTERNAL_STICKERS) ||
           BA_BITWISE_IS_BIT_SET(permission, SBR_DISCORDPERMISSION_SEND_MESSAGES_IN_THREADS) ||
           BA_BITWISE_IS_BIT_SET(permission, SBR_DISCORDPERMISSION_SEND_VOICE_MESSAGES) ||
           BA_BITWISE_IS_BIT_SET(permission, SBR_DISCORDPERMISSION_SEND_POLLS);
}

BA_Boolean SBR_DiscordPermissions_IsVoicePermission(SBR_DiscordPermissions permission) {
    return BA_BITWISE_IS_BIT_SET(permission, SBR_DISCORDPERMISSION_CREATE_INSTANT_INVITE) ||
           BA_BITWISE_IS_BIT_SET(permission, SBR_DISCORDPERMISSION_MANAGE_CHANNELS) ||
           BA_BITWISE_IS_BIT_SET(permission, SBR_DISCORDPERMISSION_ADD_REACTIONS) ||
           BA_BITWISE_IS_BIT_SET(permission, SBR_DISCORDPERMISSION_PRIORITY_SPEAKER) ||
           BA_BITWISE_IS_BIT_SET(permission, SBR_DISCORDPERMISSION_STREAM) ||
           BA_BITWISE_IS_BIT_SET(permission, SBR_DISCORDPERMISSION_VIEW_CHANNEL) ||
           BA_BITWISE_IS_BIT_SET(permission, SBR_DISCORDPERMISSION_SEND_MESSAGES) ||
           BA_BITWISE_IS_BIT_SET(permission, SBR_DISCORDPERMISSION_SEND_TTS_MESSAGES) ||
           BA_BITWISE_IS_BIT_SET(permission, SBR_DISCORDPERMISSION_MANAGE_MESSAGES) ||
           BA_BITWISE_IS_BIT_SET(permission, SBR_DISCORDPERMISSION_EMBED_LINKS) ||
           BA_BITWISE_IS_BIT_SET(permission, SBR_DISCORDPERMISSION_ATTACH_FILES) ||
           BA_BITWISE_IS_BIT_SET(permission, SBR_DISCORDPERMISSION_READ_MESSAGE_HISTORY) ||
           BA_BITWISE_IS_BIT_SET(permission, SBR_DISCORDPERMISSION_MENTION_EVERYONE) ||
           BA_BITWISE_IS_BIT_SET(permission, SBR_DISCORDPERMISSION_USE_EXTERNAL_EMOJIS) ||
           BA_BITWISE_IS_BIT_SET(permission, SBR_DISCORDPERMISSION_CONNECT) ||
           BA_BITWISE_IS_BIT_SET(permission, SBR_DISCORDPERMISSION_SPEAK) ||
           BA_BITWISE_IS_BIT_SET(permission, SBR_DISCORDPERMISSION_MUTE_MEMBERS) ||
           BA_BITWISE_IS_BIT_SET(permission, SBR_DISCORDPERMISSION_DEAFEN_MEMBERS) ||
           BA_BITWISE_IS_BIT_SET(permission, SBR_DISCORDPERMISSION_MOVE_MEMBERS) ||
           BA_BITWISE_IS_BIT_SET(permission, SBR_DISCORDPERMISSION_USE_VAD) ||
           BA_BITWISE_IS_BIT_SET(permission, SBR_DISCORDPERMISSION_MANAGE_ROLES) ||
           BA_BITWISE_IS_BIT_SET(permission, SBR_DISCORDPERMISSION_MANAGE_WEBHOOKS) ||
           BA_BITWISE_IS_BIT_SET(permission, SBR_DISCORDPERMISSION_USE_APPLICATION_COMMANDS) ||
           BA_BITWISE_IS_BIT_SET(permission, SBR_DISCORDPERMISSION_MANAGE_EVENTS) ||
           BA_BITWISE_IS_BIT_SET(permission, SBR_DISCORDPERMISSION_USE_EXTERNAL_STICKERS) ||
           BA_BITWISE_IS_BIT_SET(permission, SBR_DISCORDPERMISSION_USE_EMBEDDED_ACTIVITIES) ||
           BA_BITWISE_IS_BIT_SET(permission, SBR_DISCORDPERMISSION_USE_SOUNDBOARD) ||
           BA_BITWISE_IS_BIT_SET(permission, SBR_DISCORDPERMISSION_CREATE_EVENTS) ||
           BA_BITWISE_IS_BIT_SET(permission, SBR_DISCORDPERMISSION_USE_EXTERNAL_SOUNDS) ||
           BA_BITWISE_IS_BIT_SET(permission, SBR_DISCORDPERMISSION_SEND_VOICE_MESSAGES) ||
           BA_BITWISE_IS_BIT_SET(permission, SBR_DISCORDPERMISSION_SEND_POLLS);
}

BA_Boolean SBR_DiscordPermissions_IsStagePermission(SBR_DiscordPermissions permission) {
    return BA_BITWISE_IS_BIT_SET(permission, SBR_DISCORDPERMISSION_CREATE_INVITE) ||
           BA_BITWISE_IS_BIT_SET(permission, SBR_DISCORDPERMISSION_MANAGE_CHANNELS) ||
           BA_BITWISE_IS_BIT_SET(permission, SBR_DISCORDPERMISSION_ADD_REACTIONS) ||
           BA_BITWISE_IS_BIT_SET(permission, SBR_DISCORDPERMISSION_STREAM) ||
           BA_BITWISE_IS_BIT_SET(permission, SBR_DISCORDPERMISSION_VIEW_CHANNEL) ||
           BA_BITWISE_IS_BIT_SET(permission, SBR_DISCORDPERMISSION_SEND_MESSAGES) ||
           BA_BITWISE_IS_BIT_SET(permission, SBR_DISCORDPERMISSION_SEND_TTS_MESSAGES) ||
           BA_BITWISE_IS_BIT_SET(permission, SBR_DISCORDPERMISSION_MANAGE_MESSAGES) ||
           BA_BITWISE_IS_BIT_SET(permission, SBR_DISCORDPERMISSION_EMBED_LINKS) ||
           BA_BITWISE_IS_BIT_SET(permission, SBR_DISCORDPERMISSION_ATTACH_FILES) ||
           BA_BITWISE_IS_BIT_SET(permission, SBR_DISCORDPERMISSION_READ_MESSAGE_HISTORY) ||
           BA_BITWISE_IS_BIT_SET(permission, SBR_DISCORDPERMISSION_MENTION_EVERYONE) ||
           BA_BITWISE_IS_BIT_SET(permission, SBR_DISCORDPERMISSION_USE_EXTERNAL_EMOJIS) ||
           BA_BITWISE_IS_BIT_SET(permission, SBR_DISCORDPERMISSION_CONNECT) ||
           BA_BITWISE_IS_BIT_SET(permission, SBR_DISCORDPERMISSION_MUTE_MEMBERS) ||
           BA_BITWISE_IS_BIT_SET(permission, SBR_DISCORDPERMISSION_MOVE_MEMBERS) ||
           BA_BITWISE_IS_BIT_SET(permission, SBR_DISCORDPERMISSION_MANAGE_ROLES) ||
           BA_BITWISE_IS_BIT_SET(permission, SBR_DISCORDPERMISSION_MANAGE_WEBHOOKS) ||
           BA_BITWISE_IS_BIT_SET(permission, SBR_DISCORDPERMISSION_USE_APPLICATION_COMMANDS) ||
           BA_BITWISE_IS_BIT_SET(permission, SBR_DISCORDPERMISSION_REQUEST_TO_SPEAK) ||
           BA_BITWISE_IS_BIT_SET(permission, SBR_DISCORDPERMISSION_MANAGE_EVENTS) ||
           BA_BITWISE_IS_BIT_SET(permission, SBR_DISCORDPERMISSION_USE_EXTERNAL_STICKERS) ||
           BA_BITWISE_IS_BIT_SET(permission, SBR_DISCORDPERMISSION_CREATE_EVENTS) ||
           BA_BITWISE_IS_BIT_SET(permission, SBR_DISCORDPERMISSION_SEND_VOICE_MESSAGES) ||
           BA_BITWISE_IS_BIT_SET(permission, SBR_DISCORDPERMISSION_SEND_POLLS);
}

