cmake_minimum_required(VERSION 3.28)
project(SelfBotRewrite C)

set(CMAKE_C_STANDARD 11)

add_subdirectory(dependencies/BaconAPI)
add_subdirectory(dependencies/curl)

add_executable(SelfBotRewrite source/Main.c
        source/Token.c
        source/Settings.c
        include/WebSocket/cURL.h
        source/WebSocket/cURL.c)

target_include_directories(SelfBotRewrite PUBLIC include)
target_link_libraries(SelfBotRewrite PUBLIC BaconAPI libcurl)