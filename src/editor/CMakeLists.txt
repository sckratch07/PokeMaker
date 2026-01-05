# src/Core/CMakeLists.txt
cmake_minimum_required(VERSION 3.5)
project(Editor LANGUAGES CXX)

# Librarie: Core
set(EDITOR_SOURCES
    src/Application.cpp
    src/PanelManager.cpp
)

add_executable(Editor main.cpp ${EDITOR_SOURCES})
target_include_directories(Editor
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(Editor PUBLIC Core ImGui-SFML::ImGui-SFML imgui portable_file_dialogs)