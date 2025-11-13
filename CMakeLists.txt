cmake_minimum_required(VERSION 3.20)
project(PokeMaker VERSION 0.1 LANGUAGES CXX)

# Options
option(BUILD_EDITOR "Build the editor application" ON)
option(BUILD_GAME "Build the game runtime" ON)
option(BUILD_TESTS "Build unit tests" OFF)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Install prefix convenience
if(NOT CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/install" CACHE PATH "Install path" FORCE)
endif()

include(FetchContent)

# nlohmann/json
FetchContent_Declare(
  nlohmann_json
  GIT_REPOSITORY https://github.com/nlohmann/json.git
  GIT_TAG v3.12.0
)
FetchContent_MakeAvailable(nlohmann_json)

# EnTT (ECS)
FetchContent_Declare(
  entt
  GIT_REPOSITORY https://github.com/skypjack/entt.git
  GIT_TAG v3.15.0
)
FetchContent_MakeAvailable(entt)

# SFML
FetchContent_Declare(
  sfml
  GIT_REPOSITORY https://github.com/SFML/SFML.git
  GIT_TAG 3.0.2
)
FetchContent_MakeAvailable(sfml)

# ImGui (docking branch)
add_subdirectory(extern/imgui)

set(IMGUI_DIR ${imgui_SOURCE_DIR})
set(IMGUI_SFML_FIND_SFML OFF)

# ImGui-SFML
FetchContent_Declare(
  imgui-sfml
  GIT_REPOSITORY https://github.com/SFML/imgui-sfml.git
  GIT_TAG v3.0
)
FetchContent_MakeAvailable(imgui-sfml)

# tinyfiledialogs
FetchContent_Declare(
  tinyfiledialogs
  GIT_REPOSITORY https://github.com/native-toolkit/tinyfiledialogs.git
  GIT_TAG 2.9.3
)
FetchContent_MakeAvailable(tinyfiledialogs)

#add_subdirectory(src/core)
#add_subdirectory(src/engine)
#add_subdirectory(src/renderer)

#if(BUILD_EDITOR)
#  add_subdirectory(src/editor)
#endif()

#if(BUILD_GAME)
#  add_subdirectory(src/game)
#endif()

#if(BUILD_TESTS)
#  add_subdirectory(tests)
#endif()

# Install rules (basic)
install(DIRECTORY assets DESTINATION .)

message(STATUS "Configuration summary:")
message(STATUS " BUILD_EDITOR: ${BUILD_EDITOR}")
message(STATUS " BUILD_GAME : ${BUILD_GAME}")
message(STATUS " BUILD_TESTS : ${BUILD_TESTS}")