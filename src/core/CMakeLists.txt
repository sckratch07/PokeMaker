# src/Core/CMakeLists.txt
cmake_minimum_required(VERSION 3.5)
project(Core LANGUAGES CXX)

# Librarie: Core
set(CORE_SOURCES
    src/EntityManager.cpp
    src/Logger.cpp
    src/Project.cpp
    src/ProjectManager.cpp
    src/Map.cpp
)

add_library(Core STATIC ${CORE_SOURCES})

target_include_directories(Core
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Core est header-first friendly
target_compile_features(Core PUBLIC cxx_std_20)
set_target_properties(Core PROPERTIES POSITION_INDEPENDENT_CODE ON)

# Dépendence de Core:
target_link_libraries(Core PUBLIC EnTT::EnTT nlohmann_json::nlohmann_json SFML::Graphics SFML::Window SFML::System spdlog::spdlog)
