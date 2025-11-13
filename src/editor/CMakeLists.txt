project(editor)

# Récupérer les .cpp
set(EDITOR_SOURCES
  src/main.cpp
  src/EditorApp.cpp
  src/EditorUI.cpp
)

# Récupérer les .hpp
set(EDITOR_HEADERS
  include/editor/EditorApp.hpp
  include/editor/EditorUI.hpp
)

# Création de l'exécutable
add_executable(tile_editor ${EDITOR_SOURCES} ${EDITOR_HEADERS})
target_include_directories(tile_editor PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Version C++ 20
target_compile_features(tile_editor PUBLIC cxx_std_20)

# Ajout des librairies
# - core, engine, renderer
# - SFML
# - ImGui + ImGui-SFML
# - tinyfiledialogs
target_link_libraries(tile_editor PRIVATE
  core
  engine
  renderer
  sfml-graphics sfml-window sfml-system sfml-audio
  imgui
  imgui-sfml
  tinyfiledialogs
)

# Preprocessor definitions for ImGui-SFML backend
target_compile_definitions(tile_editor PRIVATE IMGUI_IMPL_OPENGL_LOADER_GLAD=0)

# Copie le dossier asset dans le fichier source
add_custom_command(TARGET tile_editor POST_BUILD
COMMAND ${CMAKE_COMMAND} -E make_directory "$<TARGET_FILE_DIR:tile_editor>/assets"
COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_SOURCE_DIR}/assets" "$<TARGET_FILE_DIR:tile_editor>/assets"
)
