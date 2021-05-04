cmake_minimum_required(VERSION 3.10)
project("Legend Of Heroes" VERSION 1.0)

set(CMAKE_CXX_STANDARD 14)

file(GLOB game_SRC CONFIGURE_DEPENDS "header/*.h" "source/*.cpp")
file(GLOB imgui_SRC CONFIGURE_DEPENDS "imgui/*.h" "imgui/*.cpp" "imgui/GL/*")
include_directories(SYSTEM ./header )
add_executable(game main/main.cpp ${game_SRC} ${imgui_SRC})
add_library(game_LIB STATIC ${game_SRC})