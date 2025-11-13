# Core utilities: resource manager, file utils, serialization helpers
project(core)

# Récupérer tout les .hpp et .cpp
file(GLOB_RECURSE CORE_HEADERS include/core/*.hpp)
file(GLOB_RECURSE CORE_SOURCES src/*.cpp)

# Créer la librairie core
add_library(core STATIC ${CORE_SOURCES} ${CORE_HEADERS})
target_include_directories(core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Version C++ 20
target_compile_features(core PUBLIC cxx_std_20)

# Ajout de nlohmann
target_link_libraries(core PUBLIC nlohmann_json::nlohmann_json)
