cmake_minimum_required(VERSION 3.28)
project(SelfBotRewrite C)

set(CMAKE_C_STANDARD 11)

add_subdirectory(dependencies/BaconAPI)

add_executable(SelfBotRewrite source/Main.c
        source/Token.c)

target_include_directories(SelfBotRewrite PUBLIC include)
target_link_libraries(SelfBotRewrite PUBLIC BaconAPI)