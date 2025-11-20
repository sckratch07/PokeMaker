# src/Game/CMakeLists.txt
cmake_minimum_required(VERSION 3.21)
project(GameApp LANGUAGES CXX)

# Executable: Game
set(GAME_SOURCES
    main.cpp
    src/GameApplication.cpp
    src/Map.cpp
    src/Tile.cpp
    src/TileBehavior.cpp
    src/TileLayer.cpp
)

add_executable(Game ${GAME_SOURCES})

target_include_directories(Game
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Version C++ 20
target_compile_features(Game PRIVATE cxx_std_20)

# Dépendence de Game:
target_link_libraries(Game
    PRIVATE
        Engine
        Renderer
        Core
        sfml-graphics
        sfml-window
        sfml-system
        sfml-audio
        nlohmann_json::nlohmann_json
)

# Organisation pour l'IDE
set_target_properties(Game PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

# Copie du dossier ressource dans la build
if(DEFINED RESOURCES_PATH)
    add_custom_command(TARGET Game POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E make_directory
            "${CMAKE_BINARY_DIR}/bin/resources"
        COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${RESOURCES_PATH}"
            "${CMAKE_BINARY_DIR}/bin/resources"
        COMMENT "Copying resources for Game"
    )
endif()

set_target_properties(Game PROPERTIES FOLDER "PokeMaker/Apps")
