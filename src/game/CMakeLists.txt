# src/game/CMakeLists.txt
cmake_minimum_required(VERSION 3.20)
project(game)

file(GLOB_RECURSE GAME_HEADERS "include/*.hpp" "include/*.h")
file(GLOB_RECURSE GAME_SOURCES "src/*.cpp" "src/*.c")

add_executable(tile_game ${GAME_HEADERS} ${GAME_SOURCES})

target_include_directories(tile_game PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(tile_game PRIVATE core engine renderer)

# Output dir
set_target_properties(tile_game PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

target_compile_features(tile_game PRIVATE cxx_std_20)
target_compile_definitions(tile_game PRIVATE "BUILD_GAME")
