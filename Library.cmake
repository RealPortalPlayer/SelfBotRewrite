project(libSelfBotRemake)

add_library(libSelfBotRemake STATIC ${SOURCE})

target_include_directories(libSelfBotRemake PUBLIC include)

target_compile_definitions(libSelfBotRemake PUBLIC DISCORD_API_VERSION=${DISCORD_API_VERSION}
                                                   DISCORD_ROOT_URL="${DISCORD_ROOT_URL}"
                                                   DISCORD_API_URL="${DISCORD_API_URL}"
                                                   DISCORD_WEBSOCKET_URL="${DISCORD_WEBSOCKET_URL}"
                                                   DISCORD_DEPRECATED_API_VERSION=${DISCORD_DEPRECATED_API_VERSION})

target_link_libraries(libSelfBotRemake PUBLIC BaconAPI libcurl)

ba_strip_static(libSelfBotRemake)