project(engine)

# Récupérer tout les .hpp et .cpp
file(GLOB_RECURSE ENGINE_HEADERS include/engine/*.hpp)
file(GLOB_RECURSE ENGINE_SOURCES src/*.cpp)

# Création de la librairie
add_library(engine STATIC ${ENGINE_SOURCES} ${ENGINE_HEADERS})
target_include_directories(engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Version C++ 20
target_compile_features(engine PUBLIC cxx_std_20)

# Ajout d'EnTT et SFML
target_link_libraries(engine PUBLIC core EnTT::EnTT sfml-graphics)

