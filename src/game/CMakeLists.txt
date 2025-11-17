project(game)

# Récupération des .cpp
set(GAME_SOURCES
  src/main.cpp
  src/GameApp.cpp
)

# Récupération des .hpp
set(GAME_HEADERS
  include/game/GameApp.hpp
)

# Création de l'exécutable
add_executable(pokemaker_game ${GAME_SOURCES} ${GAME_HEADERS})
target_include_directories(pokemaker_game PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Version C++ 20
target_compile_features(pokemaker_game PUBLIC cxx_std_20)

# Ajout des librairies
# - core, engine, renderer
# - SFML
target_link_libraries(pokemaker_game PRIVATE
  core
  engine
  renderer
  sfml-graphics sfml-window sfml-system sfml-audio
)

# Copie le dossier asset dans le fichier source
add_custom_command(TARGET tile_game POST_BUILD
COMMAND ${CMAKE_COMMAND} -E make_directory "$<TARGET_FILE_DIR:tile_game>/assets"
COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_SOURCE_DIR}/assets" "$<TARGET_FILE_DIR:tile_game>/assets"
)