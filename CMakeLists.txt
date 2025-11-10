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
CPMAddPackage("gh:skypjack/entt@v3.11.0") # adjust tag if you want

# nlohmann/json
CPMAddPackage("gh:nlohmann/json@v3.11.2")

# spdlog
CPMAddPackage("gh:gabime/spdlog@v1.11.0")

CPMAddPackage(
  NAME SFML
  GITHUB_REPOSITORY "SFML/SFML"
  GIT_TAG "3.0.2"
  OPTIONS "BUILD_SHARED_LIBS=OFF" # prefer static for bundling; adjust as needed
)

# ImGui (docking branch)
# We'll fetch upstream imgui and then a binding imgui-sfml
CPMAddPackage(
  NAME imgui
  GITHUB_REPOSITORY "ocornut/imgui"
  GIT_TAG "docking"
)

# ImGui-SFML binding (for rendering ImGui with SFML)
CPMAddPackage(
  NAME imgui-sfml
  GITHUB_REPOSITORY "eliasdaler/imgui-sfml"
  GIT_TAG "v2.6" # adjust if needed
)

# tinyfiledialogs (simple header+source)
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
