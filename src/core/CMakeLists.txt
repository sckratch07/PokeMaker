project(core)

# Récupérer tout les .hpp et .cpp
set(CORE_HEADERS
    
)

set(CORE_SOURCES

)

# Créer la librairie core
add_library(core STATIC ${CORE_SOURCES} ${CORE_HEADERS})
target_include_directories(core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Version C++ 20
target_compile_features(core PUBLIC cxx_std_20)

# Ajout de nlohmann et SFML
target_link_libraries(core PRIVATE sfml-graphics nlohmann_json::nlohmann_json)