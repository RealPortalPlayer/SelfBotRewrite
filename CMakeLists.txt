cmake_minimum_required(VERSION 3.28)
project(SelfBotRewrite C)

set(CMAKE_C_STANDARD 11)
set(DISCORD_API_VERSION 10)
set(DISCORD_ROOT_URL "https://discord.com")
set(DISCORD_API_URL "${DISCORD_ROOT_URL}/api/v${DISCORD_API_VERSION}")
set(DISCORD_WEBSOCKET_URL "wss://gateway.discord.gg")
set(DISCORD_DEPRECATED_API_VERSION 8)

if(DISCORD_API_VERSION LESS_EQUAL DISCORD_DEPRECATED_API_VERSION)
    message(DEPRECATION "Discord API versions ${DISCORD_DEPRECATED_API_VERSION} and below are deprecated")
endif()

include(cURLOptions.cmake)
add_subdirectory(dependencies/BaconAPI)
add_subdirectory(dependencies/curl)

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
           source/UserAgent.c)

add_executable(SelfBotRewrite source/Main.c ${SOURCE})

target_include_directories(SelfBotRewrite PUBLIC include)
target_link_libraries(SelfBotRewrite PUBLIC BaconAPI libcurl)
target_compile_definitions(SelfBotRewrite PUBLIC DISCORD_API_VERSION=${DISCORD_API_VERSION}
                                                 DISCORD_ROOT_URL="${DISCORD_ROOT_URL}"
                                                 DISCORD_API_URL="${DISCORD_API_URL}"
                                                 DISCORD_WEBSOCKET_URL="${DISCORD_WEBSOCKET_URL}"
                                                 DISCORD_DEPRECATED_API_VERSION=${DISCORD_DEPRECATED_API_VERSION})

ba_strip(SelfBotRewrite)

include(Library.cmake)
add_subdirectory(test)