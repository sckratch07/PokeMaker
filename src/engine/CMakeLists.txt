# src/Engine/CMakeLists.txt
cmake_minimum_required(VERSION 3.5)
project(Engine LANGUAGES CXX)

# Librarie: Engine
set(ENGINE_SOURCES
    src/World.cpp
    src/Systems.cpp
    src/Systems/AnimationSystem.cpp
    src/Systems/BehaviorSystem.cpp
    src/Systems/PhysicsSystem.cpp
)

add_library(Engine STATIC ${ENGINE_SOURCES})

target_include_directories(Engine
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Engine est header-first friendly
target_compile_features(Engine PUBLIC cxx_std_20)
set_target_properties(Engine PROPERTIES POSITION_INDEPENDENT_CODE ON)

# Dépendence de Engine:
target_link_libraries(Engine PUBLIC Core EnTT::EnTT nlohmann_json::nlohmann_json sfml-graphics sfml-system)

# Include Core automatiquement
target_include_directories(Engine PUBLIC ${CMAKE_SOURCE_DIR}/src/Core/include)

# Organisation pour l'IDE
set_target_properties(Engine PROPERTIES FOLDER "PokeMaker/Libraries")
