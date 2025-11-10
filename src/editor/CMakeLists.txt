# src/editor/CMakeLists.txt
cmake_minimum_required(VERSION 3.20)
project(editor)

file(GLOB_RECURSE EDITOR_HEADERS "include/*.hpp" "include/*.h")
file(GLOB_RECURSE EDITOR_SOURCES "src/*.cpp" "src/*.c")

add_executable(tile_editor ${EDITOR_HEADERS} ${EDITOR_SOURCES})

target_include_directories(tile_editor PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Link with app libraries
target_link_libraries(tile_editor PRIVATE core engine renderer)

# ImGui + ImGui-SFML
if(TARGET imgui)
  target_link_libraries(tile_editor PRIVATE imgui)
endif()
if(TARGET imgui-sfml)
  target_link_libraries(tile_editor PRIVATE imgui-sfml)
endif()

# tinyfiledialogs
if(TARGET tinyfiledialogs)
  target_link_libraries(tile_editor PRIVATE tinyfiledialogs::tinyfiledialogs)
else()
  # fallback: tinyfiledialogs may provide a CMake target or not; try include and link manually
  # (CPM provides a target if the package root defines it)
endif()

# Platform-specific linking for SFML is handled by renderer target linking
# Add compile features
target_compile_features(tile_editor PRIVATE cxx_std_20)

# Define an RPATH for finding assets next to binary in multi-config builds (optional)
set_target_properties(tile_editor PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

# Define preprocessor for editor builds
target_compile_definitions(tile_editor PRIVATE "BUILD_EDITOR_APP")
