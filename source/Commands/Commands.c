// Copyright (c) 2024, PortalPlayer <email@portalplayer.xyz>
// Licensed under MIT <https://opensource.org/licenses/MIT>

#include <BaconAPI/Logger.h>
#include <BaconAPI/String.h>

#include "Commands/Commands.h"
#include "Commands/Command.h"
#include "Commands/TestCommand.h"
#include "Commands/HelpCommand.h"
#include "Commands/DebugCommand.h"

#define SBR_COMMANDS_REGISTER(name, description, category, type) SBR_Command_Register(#name, description, category, type, (SBR_Command_Action) &SBR_Commands_ ## name)

void SBR_Commands_Register(void) {
    BA_LOGGER_INFO("Registering all commands\n");
    SBR_COMMANDS_REGISTER(test, "Testing command", "misc", SBR_COMMAND_TYPE_CLASSIC);
    SBR_COMMANDS_REGISTER(help, "Information about each command", "information", SBR_COMMAND_TYPE_CLASSIC);
    SBR_COMMANDS_REGISTER(debug, "Shows information about the bot", "information", SBR_COMMAND_TYPE_CLASSIC);
}
