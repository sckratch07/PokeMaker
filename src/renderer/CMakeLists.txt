# src/Renderer/CMakeLists.txt
cmake_minimum_required(VERSION 3.5)
project(Renderer LANGUAGES CXX)

# Librarie: Renderer
set(RENDERER_SOURCES
    src/Camera2D.cpp
    src/MapRenderer.cpp
)

add_library(Renderer STATIC ${RENDERER_SOURCES})

target_include_directories(Renderer
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Renderer est header-first friendly
target_compile_features(Renderer PUBLIC cxx_std_20)
set_target_properties(Renderer PROPERTIES POSITION_INDEPENDENT_CODE ON)

# Dépendence de Renderer:
target_link_libraries(Renderer PUBLIC Core Engine sfml-graphics sfml-window sfml-system)

# Organisation pour l'IDE
set_target_properties(Renderer PROPERTIES FOLDER "PokeMaker/Libraries")
