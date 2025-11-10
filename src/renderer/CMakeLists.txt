# src/renderer/CMakeLists.txt
cmake_minimum_required(VERSION 3.20)
project(renderer)

file(GLOB_RECURSE RENDERER_HEADERS "include/*.hpp" "include/*.h")
file(GLOB_RECURSE RENDERER_SOURCES "src/*.cpp" "src/*.c")

add_library(renderer STATIC ${RENDERER_HEADERS} ${RENDERER_SOURCES})
target_include_directories(renderer PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)

# Link SFML (graphics, window, system, audio if needed)
if(TARGET SFML::SFML)
  target_link_libraries(renderer PUBLIC SFML::SFML)
else()
  find_package(SFML 2.5 COMPONENTS graphics window system audio REQUIRED)
  target_link_libraries(renderer PUBLIC sfml-graphics sfml-window sfml-system sfml-audio)
endif()

# Link core + engine if renderer uses them
target_link_libraries(renderer PUBLIC core engine)

target_compile_features(renderer PUBLIC cxx_std_20)
target_compile_definitions(renderer PUBLIC "RENDERER_LIBRARY")

set_target_properties(renderer PROPERTIES OUTPUT_NAME "pokemaker_renderer")
