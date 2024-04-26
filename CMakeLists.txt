cmake_minimum_required(VERSION 3.28)
project(SelfBotRewrite C)

set(CMAKE_C_STANDARD 11)
set(DISCORD_API_VERSION 10)
set(DISCORD_ROOT_URL "https://discord.com")
set(DISCORD_API_URL "${DISCORD_ROOT_URL}/api/v${DISCORD_API_VERSION}")
set(DISCORD_WEBSOCKET_URL "wss://gateway.discord.gg/?v=${DISCORD_API_VERSION}&encoding=json")
set(DISCORD_DEPRECATED_API_VERSION 8)
set(DISCORD_CDN_URL "https://cdn.discordapp.com")

if(DISCORD_API_VERSION LESS_EQUAL DISCORD_DEPRECATED_API_VERSION)
    message(DEPRECATION "Discord API versions ${DISCORD_DEPRECATED_API_VERSION} and below are deprecated")
endif()

include(cURLOptions.cmake)
add_subdirectory(dependencies/BaconAPI)
add_subdirectory(dependencies/curl)
add_subdirectory(dependencies/json-c)

set(VERSION "1.0.0-incomplete")

if(CMAKE_BUILD_TYPE STREQUAL "Debug" OR CMAKE_BUILD_TYPE STREQUAL "RelWithDebInfo")
    add_compile_definitions(DEBUG BA_ALLOW_DEBUG_LOGS)
elseif(BA_ALLOW_DEBUG_LOGS)
    add_compile_definitions(BA_ALLOW_DEBUG_LOGS)
endif()

set(SOURCE source/Token.c
           source/Settings.c
           source/WebSocket/cURL.c
           source/Discord/Snowflake.c
           source/Discord/Gateway/Event.c
           source/Discord/Gateway/Error.c
           source/UserAgent.c
           source/Discord/Permissions.c
           source/Discord/Configuration.c
           source/Prefix.c
           source/Discord/Gateway/Events.c
           source/Threads/Heartbeat.c
           source/MainLoop.c
           source/Discord/Gateway/Gateway.c
           source/Threads/RateLimit.c)

add_executable(SelfBotRewrite source/Main.c ${SOURCE})

target_include_directories(SelfBotRewrite PUBLIC include)
target_link_libraries(SelfBotRewrite PUBLIC BaconAPI libcurl json-c)
target_compile_definitions(SelfBotRewrite PUBLIC SBR_DISCORD_API_VERSION=${DISCORD_API_VERSION}
                                                 SBR_DISCORD_ROOT_URL="${DISCORD_ROOT_URL}"
                                                 SBR_DISCORD_API_URL="${DISCORD_API_URL}"
                                                 SBR_DISCORD_WEBSOCKET_URL="${DISCORD_WEBSOCKET_URL}"
                                                 SBR_DISCORD_DEPRECATED_API_VERSION=${DISCORD_DEPRECATED_API_VERSION}
                                                 SBR_DISCORD_CDN_URL="${DISCORD_CDN_URL}"
                                                 SRB_VERSION="${VERSION}")

ba_strip(SelfBotRewrite)

include(Library.cmake)
add_subdirectory(test)