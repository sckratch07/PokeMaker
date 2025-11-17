project(core)

# Récupérer tout les .hpp et .cpp
set(CORE_HEADERS
    include/Core.hpp
    include/FileUtils.hpp
    include/IDGenerator.hpp
    include/Logger.hpp
    include/MathUtils.hpp
    include/ResourceManager.hpp
    include/Serialization.hpp
    include/Types.hpp
)

set(CORE_SOURCES
    src/FileUtils.cpp
    src/ResourceManager.cpp
)

# Créer la librairie core
add_library(core STATIC ${CORE_SOURCES} ${CORE_HEADERS})
target_include_directories(core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Version C++ 20
target_compile_features(core PUBLIC cxx_std_20)

# Ajout de nlohmann et SFML
target_link_libraries(core PUBLIC sfml-graphics nlohmann_json::nlohmann_json)