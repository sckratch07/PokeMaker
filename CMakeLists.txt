################################################################################
# PokeMaker - root/CMakeLists.txt
################################################################################
# @file CMakeLists.txt
# @brief Configuration CMake principale du projet PokeMaker
# @details Ce fichier configure l'environnement de build multi-plateforme,
#          gère les dépendances externes via FetchContent et organise
#          les différents modules du projet (Core, Engine, Renderer, Game, Editor)
################################################################################

cmake_minimum_required(VERSION 3.21)

################################################################################
# Configuration du projet
################################################################################
project(PokeMaker 
    VERSION 1.0.0
    DESCRIPTION "Éditeur de jeu style Pokemon avec système de tiles"
    LANGUAGES CXX
)

################################################################################
# Standards C++ et options de compilation
################################################################################
# Utilisation de C++20 pour profiter des fonctionnalités modernes
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Organisation des binaires de sortie
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

################################################################################
# Options de build
################################################################################
# @brief Option pour choisir entre le mode Game ou Editor
# @note Game et Editor ne peuvent pas être compilés ensemble
option(BUILD_GAME "Build le mode jeu (Game)" OFF)
option(BUILD_EDITOR "Build le mode éditeur (Editor)" ON)
option(BUILD_TESTS "Build les tests unitaires" OFF)
option(ENABLE_WARNINGS "Active les warnings de compilation" ON)

# Validation: Game et Editor sont mutuellement exclusifs
if(BUILD_GAME AND BUILD_EDITOR)
    message(FATAL_ERROR 
        "BUILD_GAME et BUILD_EDITOR ne peuvent pas être activés simultanément!\n"
        "Veuillez choisir:\n"
        "  -DBUILD_GAME=ON -DBUILD_EDITOR=OFF  pour le mode jeu\n"
        "  -DBUILD_GAME=OFF -DBUILD_EDITOR=ON  pour l'éditeur"
    )
endif()

if(NOT BUILD_GAME AND NOT BUILD_EDITOR)
    message(FATAL_ERROR 
        "Au moins BUILD_GAME ou BUILD_EDITOR doit être activé!"
    )
endif()

################################################################################
# Configuration des warnings par plateforme
################################################################################
if(ENABLE_WARNINGS)
    if(MSVC)
        # Warnings pour Visual Studio
        add_compile_options(/W4 /WX-)
    else()
        # Warnings pour GCC/Clang
        add_compile_options(
            -Wall 
            -Wextra 
            -Wpedantic
            -Wno-unused-parameter
        )
    endif()
endif()

################################################################################
# Configuration spécifique à la plateforme
################################################################################
if(WIN32)
    message(STATUS "Configuration pour Windows")
    add_definitions(-DPLATFORM_WINDOWS)
    # Désactive les warnings Windows spécifiques
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
elseif(APPLE)
    message(STATUS "Configuration pour macOS")
    add_definitions(-DPLATFORM_MACOS)
elseif(UNIX)
    message(STATUS "Configuration pour Linux")
    add_definitions(-DPLATFORM_LINUX)
endif()

################################################################################
# Inclusion de FetchContent pour gérer les dépendances
################################################################################
include(FetchContent)

################################################################################
# @brief Téléchargement et configuration de SFML
# @details SFML (Simple and Fast Multimedia Library) pour le rendu 2D,
#          gestion des fenêtres, événements, audio
################################################################################
message(STATUS "Récupération de SFML...")
FetchContent_Declare(
    SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.1
    GIT_SHALLOW TRUE
)

# Options SFML: désactive les composants non nécessaires
set(SFML_BUILD_AUDIO TRUE)
set(SFML_BUILD_NETWORK FALSE)  # Pas de réseau pour le moment
set(BUILD_SHARED_LIBS FALSE)   # Build statique pour faciliter la distribution

FetchContent_MakeAvailable(SFML)

################################################################################
# @brief Téléchargement et configuration de ImGui
# @details ImGui pour l'interface utilisateur de l'éditeur
#          Version docking pour le support des fenêtres ancrables
################################################################################
message(STATUS "Récupération de ImGui...")
FetchContent_Declare(
    imgui
    GIT_REPOSITORY https://github.com/ocornut/imgui.git
    GIT_TAG docking  # Branche docking pour les fenêtres ancrables
    GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(imgui)

# ImGui nécessite une compilation manuelle (header-only + quelques .cpp)
set(IMGUI_DIR ${imgui_SOURCE_DIR})
set(IMGUI_SOURCES
    ${IMGUI_DIR}/imgui.cpp
    ${IMGUI_DIR}/imgui_demo.cpp
    ${IMGUI_DIR}/imgui_draw.cpp
    ${IMGUI_DIR}/imgui_tables.cpp
    ${IMGUI_DIR}/imgui_widgets.cpp
)

################################################################################
# @brief Téléchargement et configuration de ImGui-SFML
# @details Binding entre ImGui et SFML pour l'intégration
################################################################################
message(STATUS "Récupération de ImGui-SFML...")
FetchContent_Declare(
    imgui-sfml
    GIT_REPOSITORY https://github.com/SFML/imgui-sfml.git
    GIT_TAG 2.6.x
    GIT_SHALLOW TRUE
)

set(IMGUI_DIR ${IMGUI_DIR})
set(IMGUI_SFML_FIND_SFML OFF)
set(IMGUI_SFML_IMGUI_DEMO ON)

FetchContent_MakeAvailable(imgui-sfml)

################################################################################
# @brief Téléchargement et configuration de EnTT
# @details EnTT (Entity Component System) pour la gestion des entités du jeu
#          Header-only library, très performante
################################################################################
message(STATUS "Récupération de EnTT...")
FetchContent_Declare(
    EnTT
    GIT_REPOSITORY https://github.com/skypjack/entt.git
    GIT_TAG v3.13.2
    GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(EnTT)

################################################################################
# @brief Téléchargement et configuration de nlohmann/json
# @details Librairie JSON moderne pour C++ (sérialisation/désérialisation)
#          Utilisée pour sauvegarder les maps, configurations, etc.
################################################################################
message(STATUS "Récupération de nlohmann/json...")
FetchContent_Declare(
    json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG v3.11.3
    GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(json)

################################################################################
# Création de la librairie ImGui (statique)
################################################################################
# @brief Compile ImGui en tant que librairie statique
# @note Nécessaire car ImGui n'est pas header-only contrairement à EnTT
add_library(imgui STATIC ${IMGUI_SOURCES})
target_include_directories(imgui PUBLIC ${IMGUI_DIR})
target_compile_features(imgui PUBLIC cxx_std_20)

################################################################################
# Ajout des sous-répertoires (modules du projet)
################################################################################
# @brief Organisation modulaire du projet
# @details Chaque module est compilé séparément pour faciliter la maintenance
#          et la réutilisation du code

# Core: Fonctionnalités de base (logging, fichiers, utilitaires)
add_subdirectory(src/Core)

# Engine: Logique du moteur de jeu (systèmes ECS, ressources)
add_subdirectory(src/Engine)

# Renderer: Système de rendu 2D (SFML, caméra, layers)
add_subdirectory(src/Renderer)

# Game ou Editor (mutuellement exclusifs)
if(BUILD_GAME)
    message(STATUS "Configuration du mode GAME")
    add_subdirectory(src/Game)
elseif(BUILD_EDITOR)
    message(STATUS "Configuration du mode EDITOR")
    add_subdirectory(src/Editor)
endif()

# Tests (optionnel)
if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

################################################################################
# Installation et packaging (optionnel)
################################################################################
# @brief Configuration pour l'installation du projet
# @note Utile pour créer des packages distribués
install(TARGETS PokeMaker
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)

################################################################################
# Résumé de la configuration
################################################################################
message(STATUS "========================================")
message(STATUS "Configuration PokeMaker")
message(STATUS "========================================")
message(STATUS "Version: ${PROJECT_VERSION}")
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "Compilateur: ${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION}")
message(STATUS "C++ Standard: C++${CMAKE_CXX_STANDARD}")
message(STATUS "Build Game: ${BUILD_GAME}")
message(STATUS "Build Editor: ${BUILD_EDITOR}")
message(STATUS "Build Tests: ${BUILD_TESTS}")
message(STATUS "========================================")