# src/Editor/CMakeLists.txt
cmake_minimum_required(VERSION 3.5)
project(EditorApp LANGUAGES CXX)

# Executable: Editor
set(EDITOR_SOURCES
    src/main.cpp
    src/EditorApplication.cpp
    src/EditorUI.cpp
    src/LayerManager.cpp
    src/NPCEditor.cpp
    src/TilePalette.cpp
    src/WFCGenerator.cpp
    src/Map.cpp
    src/MapLink.cpp
    src/Project.cpp
    src/ProjectManager.cpp
    src/Tools/BrushTool.cpp
    src/Tools/FillTool.cpp
    src/Tools/SelectionTool.cpp
)

add_executable(Editor ${EDITOR_SOURCES})

target_include_directories(Editor
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Version C++ 20
target_compile_features(Editor PRIVATE cxx_std_20)

# Dépendance d'Editor:

# portable-file-dialogs (dialog natifs via tinyfiledialogs / zenity / applescript selon plateforme)
FetchContent_Declare(
  portable-file-dialogs
  GIT_REPOSITORY https://github.com/samhocevar/portable-file-dialogs.git
  GIT_TAG        0.1.0
)
FetchContent_MakeAvailable(portable-file-dialogs)

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
