cmake_minimum_required(VERSION 3.20)
project(engine)

file(GLOB_RECURSE ENGINE_HEADERS "include/*.hpp" "include/*.h")
file(GLOB_RECURSE ENGINE_SOURCES "src/*.cpp" "src/*.c")

add_library(engine STATIC ${ENGINE_HEADERS} ${ENGINE_SOURCES})
target_include_directories(engine PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)

# Dependencies: core + EnTT + nlohmann (if used here)
target_link_libraries(engine PUBLIC core)

if(TARGET EnTT::EnTT)
  target_link_libraries(engine PUBLIC EnTT::EnTT)
endif()
if(TARGET nlohmann_json::nlohmann_json)
  target_link_libraries(engine PUBLIC nlohmann_json::nlohmann_json)
endif()

target_compile_features(engine PUBLIC cxx_std_20)
target_compile_definitions(engine PUBLIC "ENGINE_LIBRARY")

set_target_properties(engine PROPERTIES OUTPUT_NAME "pokemaker_engine")
