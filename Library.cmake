project(libSelfBotRemake)

add_library(libSelfBotRemake STATIC ${SOURCE})

target_include_directories(libSelfBotRemake PUBLIC include)

target_compile_definitions(libSelfBotRemake PUBLIC SBR_DISCORD_API_VERSION=${DISCORD_API_VERSION}
                                                   SBR_DISCORD_ROOT_URL="${DISCORD_ROOT_URL}"
                                                   SBR_DISCORD_API_URL="${DISCORD_API_URL}"
                                                   SBR_DISCORD_WEBSOCKET_URL="${DISCORD_WEBSOCKET_URL}"
                                                   SBR_DISCORD_DEPRECATED_API_VERSION=${DISCORD_DEPRECATED_API_VERSION}
                                                   SBR_DISCORD_CDN_URL="${DISCORD_CDN_URL}")

target_link_libraries(libSelfBotRemake PUBLIC BaconAPI libcurl json-c)

ba_strip_static(libSelfBotRemake)