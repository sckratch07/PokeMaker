project(tests)

# Catch2
FetchContent_Declare(
catch2
GIT_REPOSITORY https://github.com/catchorg/Catch2.git
GIT_TAG v3.11.0
)
FetchContent_MakeAvailable(catch2)

# Création d'exécutable pour chaque teste
file(GLOB_RECURSE TEST_SOURCES *.cpp)
add_executable(all_tests ${TEST_SOURCES})

# Ajout de la librairie Catch2 au exécutable
target_link_libraries(all_tests PRIVATE Catch2::Catch2WithMain engine core)
