// Purpose: Gateway event
// Created on: 4/24/24 @ 12:56 PM

// Copyright (c) 2024, PortalPlayer <email@portalplayer.xyz>
// Licensed under MIT <https://opensource.org/licenses/MIT>

#pragma once

#include <BaconAPI/Storage/DynamicDictionary.h>

typedef enum {
    /**
     * @note BOT<-DISCORD
     */
    SBR_GATEWAYEVENT_CODE_DISPATCH,

    /**
     * Keep connection alive
     * @note BOT<->DISCORD
     */
    SBR_GATEWAYEVENT_CODE_HEARTBEAT,

    /**
     * Start new session
     * @note BOT->DISCORD
     */
    SBR_GATEWAYEVENT_CODE_IDENTIFY,

    /**
     * Update client presence
     * @note BOT->DISCORD
     */
    SBR_GATEWAYEVENT_CODE_PRESENCE_UPDATE,

    /**
     * Join/leave or move between voice channels
     * @note BOT->DISCORD
     */
    SBR_GATEWAYEVENT_CODE_VOICE_STATUS_UPDATE,

    /**
     * Resume previously disconnected session
     * @note BOT->DISCORD
     */
    SBR_GATEWAYEVENT_CODE_RESUME = 6,

    /**
     * Reconnect and resume as soon as possible
     * @note BOT<-DISCORD
     */
    SBR_GATEWAYEVENT_CODE_RECONNECT,

    /**
     * Information about every offline guild member inside a large guild
     * @note BOT->DISORD
     */
    SBR_GATEWAYEVENT_CODE_REQUEST_GUILD_MEMBERS,

    /**
     * Session invalidated. Recconect and indentifiy/resume
     * @note BOT<-DISCORD
     */
    SBR_GATEWAYEVENT_CODE_INVALID_SESSION,

    /**
     * Server saying hello. Contains heartbeat interval
     * @note BOT<-DISCORD
     */
    SBR_GATEWAYEVENT_CODE_HELLO,

    /**
     * Discord received our heartbeat
     * @note BOT<-DISCORD
     */
    SBR_GATEWAYEVENT_CODE_HEARTBEAT_ACKNOWLEDGE,

    /**
     * Not a real code
     */
    SBR_GATEWAYEVENT_CODE_SIZE
} SBR_GatewayEvent_Codes;

typedef struct {
    SBR_GatewayEvent_Codes operationCode;
    BA_DynamicDictionary* data;
    int sequence;
    const char* eventName;
} SBR_GatewayEvent;

BA_Boolean SBR_GatewayEvent_CanReceiveCode(SBR_GatewayEvent_Codes code);
BA_Boolean SBR_GatewayEvent_CanSendCode(SBR_GatewayEvent_Codes code);
BA_Boolean SBR_GatewayEvent_IsCodeValid(SBR_GatewayEvent_Codes code);
