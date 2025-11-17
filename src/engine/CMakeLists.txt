project(engine)

# Récupérer tout les .hpp et .cpp
set(ENGINE_HEADERS
    include/AnimatedTile.hpp
    include/AutotileWFC.hpp
    include/Components.hpp
    include/Engine.hpp
    include/Entity.hpp
    include/Layer.hpp
    include/QuestSystem.hpp
    include/Systems.hpp
    include/Tile.hpp
    include/Tilemap.hpp
    include/Tileset.hpp
    include/World.hpp
)
set(ENGINE_SOURCES
    src/AnimatedTile.cpp
    src/AutotileWFC.cpp
    src/Components.cpp
    src/Entity.cpp
    src/Layer.cpp
    src/QuestSystem.cpp
    src/Systems.cpp
    src/Tilemap.cpp
    src/Tileset.cpp
    src/World.cpp
)

# Création de la librairie
add_library(engine STATIC ${ENGINE_SOURCES} ${ENGINE_HEADERS})
target_include_directories(engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Version C++ 20
target_compile_features(engine PUBLIC cxx_std_20)

# Ajout d'EnTT et SFML
target_link_libraries(engine PUBLIC core EnTT::EnTT sfml-graphics)

