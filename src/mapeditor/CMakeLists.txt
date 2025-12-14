# src/Editor/CMakeLists.txt
cmake_minimum_required(VERSION 3.5)
project(EditorApp LANGUAGES CXX)

# Executable: Editor
set(EDITOR_SOURCES
    src/MapEditor.cpp
    src/EditorContext.cpp
    src/Layer.cpp
    src/Brush.cpp
    src/EditorUI.cpp
    src/Map/Map.cpp
    src/Map/MapSettings.cpp
    src/Tileset/Tileset.cpp
    src/Tileset/TilesetLoader.cpp
    src/System/MapRenderSystem.cpp
    src/System/TileAnimationSystem.cpp
    src/System/AutoTileSystem.cpp
    src/Shader/Shader.cpp
    src/Shader/ShaderLibrary.cpp
    src/Serialization/MapSerializer.cpp
    src/Serialization/ProjectSerializer.cpp
)

add_executable(Editor ${EDITOR_SOURCES})

target_include_directories(Editor
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Version C++ 20
target_compile_features(Editor PRIVATE cxx_std_20)

# Dépendance d'Editor:
target_link_libraries(Editor
    PRIVATE
        Core
        Engine
        Renderer
        sfml-graphics
        sfml-window
        sfml-system
        sfml-audio
        imgui
        ImGui-SFML
        nlohmann_json::nlohmann_json
        pfd
)

# Organisation pour l'IDE
set_target_properties(Editor PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

# Copie du dossier ressource dans la build
if(DEFINED RESOURCES_PATH)
    add_custom_command(TARGET Editor POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E make_directory
            "${CMAKE_BINARY_DIR}/bin/resources"
        COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${RESOURCES_PATH}"
            "${CMAKE_BINARY_DIR}/bin/resources"
        COMMENT "Copying resources for Editor"
    )
endif()

set_target_properties(Editor PROPERTIES FOLDER "PokeMaker/Apps")
