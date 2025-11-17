project(editor)

# Récupérer les .cpp
set(EDITOR_SOURCES
  src/main.cpp
  src/EditorApp.cpp
  src/EditorUI.cpp
)

# Récupérer les .hpp
set(EDITOR_HEADERS
  include/EditorApp.hpp
  include/EditorUI.hpp
)

# Création de l'exécutable
add_executable(game_editor ${EDITOR_SOURCES} ${EDITOR_HEADERS})
target_include_directories(game_editor PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Version C++ 20
target_compile_features(game_editor PUBLIC cxx_std_20)

# Ajout des librairies
# - core, engine, renderer
# - SFML
# - ImGui + ImGui-SFML
# - tinyfiledialogs
target_link_libraries(game_editor PRIVATE
  core
  engine
  renderer
  sfml-graphics sfml-window sfml-system sfml-audio
  imgui
  imgui-sfml
  tinyfiledialogs
)

# Preprocessor definitions for ImGui-SFML backend
target_compile_definitions(game_editor PRIVATE IMGUI_IMPL_OPENGL_LOADER_GLAD=0)

# Copie le dossier asset dans le fichier source
add_custom_command(TARGET game_editor POST_BUILD
COMMAND ${CMAKE_COMMAND} -E make_directory "$<TARGET_FILE_DIR:game_editor>/assets"
COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_SOURCE_DIR}/assets" "$<TARGET_FILE_DIR:game_editor>/assets"
)
