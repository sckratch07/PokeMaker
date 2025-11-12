cmake_minimum_required(VERSION 3.20)
project(core)

file(GLOB_RECURSE CORE_HEADERS "include/*.hpp" "include/*.h")
file(GLOB_RECURSE CORE_SOURCES "src/*.cpp" "src/*.c")

add_library(core STATIC ${CORE_HEADERS} ${CORE_SOURCES})
target_include_directories(core PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)

if(TARGET nlohmann_json)
  target_link_libraries(core PUBLIC nlohmann_json::nlohmann_json)
endif()

# Example defines
target_compile_definitions(core PUBLIC "CORE_LIBRARY")

# Set properties for consumers
set_target_properties(core PROPERTIES
  OUTPUT_NAME "pokemaker_core"
)
