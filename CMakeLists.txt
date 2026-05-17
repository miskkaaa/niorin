cmake_minimum_required(VERSION 3.21)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
if ("${CMAKE_SYSTEM_NAME}" STREQUAL "iOS" OR IOS)
    set(CMAKE_OSX_ARCHITECTURES "arm64")
else()
    set(CMAKE_OSX_ARCHITECTURES "arm64;x86_64")
endif()
set(CMAKE_CXX_VISIBILITY_PRESET hidden)

project(niorin VERSION 1.0.0)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*.cpp)
add_library(${PROJECT_NAME} SHARED ${SOURCES}
        src/main.cpp
        src/themes/listing.hpp
        src/themes/theme/default.hpp
        src/themes/helper.hpp
        src/cheats/level/startposition.cpp
        src/cheats/headers/global.hpp
        src/cheats/headers/global.cpp
        src/themes/color/colors.hpp
        src/themes/theme/classic.hpp
        src/cheats/global/vsync.cpp
        src/magic/global.hpp
        src/cheats/global/fpsbypass.cpp
        src/cheats/global/cbs.cpp
        src/themes/theme/mobile.hpp
        src/cheats/bypass/characterlimit.cpp
        src/cheats/bypass/characterlimit.cpp
        src/cheats/bypass/characterlength.cpp
        src/cheats/bypass/icon.cpp
        src/cheats/bypass/icon.cpp
        src/cheats/player/Noclip.cpp
)

if (NOT DEFINED ENV{GEODE_SDK})
    message(FATAL_ERROR "Unable to find Geode SDK! Please define GEODE_SDK environment variable to point to Geode")
else()
    message(STATUS "Found Geode: $ENV{GEODE_SDK}")
endif()

include(cmake/CPM.cmake)
include(cmake/embed.cmake)

add_subdirectory($ENV{GEODE_SDK} ${CMAKE_CURRENT_BINARY_DIR}/geode)

setup_geode_mod(${PROJECT_NAME})
CPMAddPackage("gh:matcool/gd-imgui-cocos#b93f08ccef778a53ebba09b20c347f6a63980119") # specify a commit!

target_link_libraries(${PROJECT_NAME} imgui-cocos)

set(FONT_TTF_PATH ${imgui_SOURCE_DIR}resources/fonts/DroidSans.ttf)
FileEmbedAdd("${FONT_TTF_PATH}")
set(FONT_TTF_PATH ${imgui_SOURCE_DIR}resources/fonts/NotoSans.ttf)
FileEmbedAdd("${FONT_TTF_PATH}")

target_link_libraries(${PROJECT_NAME} embedded_files)