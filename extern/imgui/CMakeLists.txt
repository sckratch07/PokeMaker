cmake_minimum_required(VERSION 3.20)
project(imgui)

file(GLOB_RECURSE IMGUI_HEADERS "include/*.hpp" "include/*.h")
file(GLOB_RECURSE IMGUI_SOURCES "src/*.cpp" "src/*.c")

add_library(imgui STATIC ${IMGUI_HEADERS} ${IMGUI_SOURCES})
target_include_directories(imgui PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)

# Example defines
target_compile_definitions(imgui PUBLIC "IMGUI_LIBRARY")
