// Copyright (c) 2024, PortalPlayer <email@portalplayer.xyz>
// Licensed under MIT <https://opensource.org/licenses/MIT>

#include <string.h>
#include <BaconAPI/Logger.h>
#include <BaconAPI/Math/Bitwise.h>

#include "Discord/Gateway/Dispatch.h"
#include "Discord/Gateway/Gateway.h"
#include "Bot.h"
#include "MainLoop.h"
#include "Discord/Objects/Message.h"
#include "Events.h"

#define SBR_GATEWAYDISPATCH_CREATE_EVENT_FUNCTION_HEADER(name) static void SBR_GatewayDispatch_Action ## name(json_object* data)

#define SBR_GATEWAYDISPATCH_CREATE_ENTRY(code) \
{                                              \
    #code,                                      \
    SBR_GatewayDispatch_Action ## code         \
}

SBR_GATEWAYDISPATCH_CREATE_EVENT_FUNCTION_HEADER(READY);
SBR_GATEWAYDISPATCH_CREATE_EVENT_FUNCTION_HEADER(RESUMED);
SBR_GATEWAYDISPATCH_CREATE_EVENT_FUNCTION_HEADER(MESSAGE_CREATE);

static SBR_GatewayDispatch_Information sbrGatewayDispatches[] = {
    SBR_GATEWAYDISPATCH_CREATE_ENTRY(READY),
    SBR_GATEWAYDISPATCH_CREATE_ENTRY(RESUMED),
    SBR_GATEWAYDISPATCH_CREATE_ENTRY(MESSAGE_CREATE)
};
const size_t lengthOfDispatchArray = sizeof(sbrGatewayDispatches) / sizeof(sbrGatewayDispatches[0]);

const SBR_GatewayDispatch_Information* SBR_GatewayDispatch_Get(const char* code) {
    for (int index = 0; index < lengthOfDispatchArray; index++) {
        if (strcmp(sbrGatewayDispatches[index].code, code) != 0)
            continue;

        return &sbrGatewayDispatches[index];
    }

    return NULL;
}

SBR_GATEWAYDISPATCH_CREATE_EVENT_FUNCTION_HEADER(READY) {
    // TODO: API version
    json_object* user = json_object_object_get(data, "user");
    json_object* sessionId = json_object_object_get(data, "session_id");
    json_object* resumeGatewayUrl = json_object_object_get(data, "resume_gateway_url");

    if (user == NULL) {
        BA_LOGGER_ERROR("Malformed packet: missing JSON field\n");
        SBR_MainLoop_SignalDisconnected();
        return;
    }
        
    SBR_Bot_Set(SBR_DiscordUser_Create(user));

    if (!BA_BITWISE_IS_BIT_SET(SBR_Bot_Get()->customFlags, SBR_DISCORDUSER_CUSTOM_FLAG_BOT))
        BA_LOGGER_WARN("\"Bot\" user is not actually a bot. Self-bots are against Discords TOS\n");
        
    SBR_Gateway_SetResumeData(json_object_get_string(resumeGatewayUrl), json_object_get_string(sessionId));
    BA_LOGGER_TRACE("Resume URL: %s\n"
                    "Session ID: %s\n", SBR_Gateway_GetResumeURL(), SBR_Gateway_GetSessionID());
    SBR_Events_Ready();
}

SBR_GATEWAYDISPATCH_CREATE_EVENT_FUNCTION_HEADER(RESUMED) {
    BA_LOGGER_DEBUG("Successfully reconnected and resumed\n");
}

SBR_GATEWAYDISPATCH_CREATE_EVENT_FUNCTION_HEADER(MESSAGE_CREATE) {
    SBR_DiscordMessage* message = SBR_DiscordMessage_Create(data);

    if (message == NULL) {
        BA_LOGGER_ERROR("Failed to parse message: %s\n", json_object_to_json_string(data));
        return;
    }

    SBR_Events_MessageSent(message);
    SBR_DiscordMessage_Deallocate(message);
}
