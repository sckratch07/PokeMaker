cmake_minimum_required(VERSION 3.20)
project(PokeMaker CXX)

# -------------------------------------------------------------------
# Global settings
# -------------------------------------------------------------------
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

option(BUILD_EDITOR "Build Editor" ON)
option(BUILD_GAME "Build Game" ON)
option(BUILD_TESTS "Build Tests" OFF)

# Build types defaults
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Build type" FORCE)
endif()

# -------------------------------------------------------------------
# Bootstrap CPM.cmake
# -------------------------------------------------------------------
if(NOT EXISTS "${CMAKE_SOURCE_DIR}/cmake/CPM.cmake")
  message(STATUS "Downloading CPM.cmake to ${CMAKE_SOURCE_DIR}/cmake/CPM.cmake")
  file(DOWNLOAD
    "https://github.com/cpm-cmake/CPM.cmake/releases/latest/download/CPM.cmake"
    "${CMAKE_SOURCE_DIR}/cmake/CPM.cmake"
    SHOW_PROGRESS
    TLS_VERIFY ON
  )
endif()
include("${CMAKE_SOURCE_DIR}/cmake/CPM.cmake")

# -------------------------------------------------------------------
# CPM packages
# -------------------------------------------------------------------

# EnTT
CPMAddPackage(
  NAME EnTT
  GITHUB_REPOSITORY "skypjack/entt"
  GIT_TAG "v3.15.0"
)

# nlohmann/json
CPMAddPackage(
  NAME nlohmann
  GITHUB_REPOSITORY "nlohmann/json"
  GIT_TAG "v3.12.0"
)

# SFML
CPMAddPackage(
  NAME SFML
  GITHUB_REPOSITORY "SFML/SFML"
  GIT_TAG "3.0.2"
)

# ImGui and ImGui-SFML
CPMAddPackage(
  NAME ImGui
  GITHUB_REPOSITORY "ocornut/imgui"
  GIT_TAG "v1.92.4-docking"
)

set(IMGUI_DIR ${ImGui_SOURCE_DIR})

CPMAddPackage(
  NAME ImGui-SFML
  GITHUB_REPOSITORY "eliasdaler/imgui-sfml"
  GIT_TAG "v2.6"
)

# tinyfiledialogs
CPMAddPackage(
  NAME tinyfiledialogs
  GITHUB_REPOSITORY "native-toolkit/tinyfiledialogs"
  GIT_TAG "master"
)

# -------------------------------------------------------------------
# Add subdirectories (library/exe modules)
# -------------------------------------------------------------------
add_subdirectory(src/core)
add_subdirectory(src/engine)
add_subdirectory(src/renderer)

if(BUILD_EDITOR)
  add_subdirectory(src/editor)
endif()
if(BUILD_GAME)
  add_subdirectory(src/game)
endif()

if(BUILD_TESTS)
  add_subdirectory(tests)
endif()

add_executable(PokeMaker main.cpp)

target_link_libraries(PokeMaker PRIVATE SFML::Graphics SFML::Window SFML::Audio SFML::System)