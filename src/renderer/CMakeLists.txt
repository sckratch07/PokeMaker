project(renderer)

# Récupération des .hpp et .cpp
file(GLOB_RECURSE RENDERER_HEADERS include/renderer/*.hpp)
file(GLOB_RECURSE RENDERER_SOURCES src/*.cpp)

# Création de la librairie renderer
add_library(renderer STATIC ${RENDERER_SOURCES} ${RENDERER_HEADERS})
target_include_directories(renderer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Version C++ 20
target_compile_features(renderer PUBLIC cxx_std_20)

# Ajout de la SFML
target_link_libraries(renderer PUBLIC core sfml-graphics sfml-window sfml-system sfml-audio)
