# ============================================================================
# PokeMaker - Éditeur de jeu Pokémon-like
# ============================================================================
# CMakeLists.txt racine du projet
# 
# Ce fichier configure l'ensemble du projet PokeMaker, incluant :
# - La détection et configuration multi-plateforme (Windows, Linux, macOS)
# - La gestion des dépendances via FetchContent (SFML, ImGui, EnTT, nlohmann_json)
# - La compilation des modules Core, Engine, Renderer, Game et Editor
# - Les options de build (Debug/Release, choix entre Game et Editor)
# - La configuration de Doxygen pour la documentation
#
# ============================================================================

# ----------------------------------------------------------------------------
# Configuration CMake minimale et projet
# ----------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.5)

# Définition du projet avec version et langages
project(PokeMaker 
    VERSION 1.0.0
    LANGUAGES CXX
    DESCRIPTION "Éditeur de jeu C++"
)

# ----------------------------------------------------------------------------
# Standards C++ et politiques
# ----------------------------------------------------------------------------
# Utilisation du standard C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ----------------------------------------------------------------------------
# Options de build configurables par l'utilisateur
# ----------------------------------------------------------------------------
# Option pour choisir entre compiler le jeu ou l'éditeur
# Note: Game et Editor ne peuvent pas être compilés ensemble
option(BUILD_GAME "Compiler l'application de jeu" ON)
option(BUILD_EDITOR "Compiler l'éditeur de niveau" OFF)

# Options de build additionnelles
option(BUILD_SHARED_LIBS "Compiler les bibliothèques en partagé" OFF)
option(BUILD_TESTS "Compiler les tests unitaires" OFF)

# Vérification que Game et Editor ne sont pas activés simultanément
if(BUILD_GAME AND BUILD_EDITOR)
    message(FATAL_ERROR 
        "BUILD_GAME et BUILD_EDITOR ne peuvent pas être activés simultanément.\n"
        "Veuillez choisir l'un ou l'autre :\n"
        "  -DBUILD_GAME=ON -DBUILD_EDITOR=OFF  (pour le jeu)\n"
        "  -DBUILD_GAME=OFF -DBUILD_EDITOR=ON  (pour l'éditeur)"
    )
endif()

# Si aucun n'est activé, activer le jeu par défaut
if(NOT BUILD_GAME AND NOT BUILD_EDITOR)
    message(STATUS "Aucun mode sélectionné, activation de BUILD_GAME par défaut")
    set(BUILD_GAME ON)
endif()

# ----------------------------------------------------------------------------
# Configuration des chemins de sortie
# ----------------------------------------------------------------------------
# Tous les exécutables et bibliothèques seront placés dans ces dossiers
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Chemin vers les ressources (relatif à l'exécutable)
set(RESOURCES_PATH "${CMAKE_SOURCE_DIR}/resources")

# ----------------------------------------------------------------------------
# Configuration multi-plateforme
# ----------------------------------------------------------------------------
# Détection du système d'exploitation et configuration spécifique
if(WIN32)
    message(STATUS "Configuration pour Windows")
    # Options spécifiques Windows
    add_definitions(-DWIN32_LEAN_AND_MEAN)
    add_definitions(-DNOMINMAX)
    
    # Pour éviter la console en mode Release sur Windows
    if(MSVC)
        set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} /SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")
    endif()
    
elseif(APPLE)
    message(STATUS "Configuration pour macOS")
    # Options spécifiques macOS
    set(CMAKE_OSX_DEPLOYMENT_TARGET "10.15" CACHE STRING "Minimum macOS version")
    
elseif(UNIX)
    message(STATUS "Configuration pour Linux")
    # Options spécifiques Linux
    # Aucune configuration particulière nécessaire pour le moment
endif()

# ----------------------------------------------------------------------------
# Inclusion de FetchContent pour gérer les dépendances
# ----------------------------------------------------------------------------
include(FetchContent)

# Configuration globale de FetchContent
set(FETCHCONTENT_QUIET FALSE)
set(FETCHCONTENT_UPDATES_DISCONNECTED ON)

# ----------------------------------------------------------------------------
# Dépendance : SFML (Simple and Fast Multimedia Library)
# ----------------------------------------------------------------------------
# SFML est utilisé pour le rendu graphique, l'audio et la gestion des entrées
message(STATUS "Configuration de SFML...")

FetchContent_Declare(
    sfml
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.2
    GIT_SHALLOW TRUE
    GIT_PROGRESS TRUE
)

# Options SFML (désactiver ce dont on n'a pas besoin)
set(SFML_BUILD_AUDIO ON)
set(SFML_BUILD_NETWORK OFF)
set(BUILD_SHARED_LIBS OFF)

FetchContent_MakeAvailable(sfml)

# ----------------------------------------------------------------------------
# Dépendance : Dear ImGui (Interface graphique immédiate)
# ----------------------------------------------------------------------------
# ImGui est utilisé pour l'interface de l'éditeur
message(STATUS "Configuration de ImGui...")

FetchContent_Declare(
    imgui
    GIT_REPOSITORY https://github.com/ocornut/imgui.git
    GIT_TAG v1.91.1-docking
    GIT_SHALLOW TRUE
    GIT_PROGRESS TRUE
)

FetchContent_GetProperties(imgui)
if(NOT imgui_POPULATED)
    FetchContent_Populate(imgui)
    
    # Création d'une bibliothèque pour ImGui
    # ImGui n'a pas de CMakeLists.txt, nous devons le créer manuellement
    add_library(imgui STATIC
        ${imgui_SOURCE_DIR}/imgui.cpp
        ${imgui_SOURCE_DIR}/imgui_demo.cpp
        ${imgui_SOURCE_DIR}/imgui_draw.cpp
        ${imgui_SOURCE_DIR}/imgui_tables.cpp
        ${imgui_SOURCE_DIR}/imgui_widgets.cpp
    )
    
    target_include_directories(imgui PUBLIC ${imgui_SOURCE_DIR})
    
    # Définir le dossier pour l'organisation dans l'IDE
    set_target_properties(imgui PROPERTIES FOLDER "External")
endif()

# ----------------------------------------------------------------------------
# Dépendance : ImGui-SFML (Binding ImGui pour SFML)
# ----------------------------------------------------------------------------
# Permet d'utiliser ImGui avec SFML
message(STATUS "Configuration de ImGui-SFML...")

FetchContent_Declare(
    imgui_sfml
    GIT_REPOSITORY https://github.com/SFML/imgui-sfml.git
    GIT_TAG v3.0
    GIT_SHALLOW TRUE
    GIT_PROGRESS TRUE
)

# Options ImGui-SFML
set(IMGUI_DIR ${imgui_SOURCE_DIR})
set(IMGUI_SFML_FIND_SFML OFF)
set(IMGUI_SFML_IMGUI_DEMO ON)

FetchContent_MakeAvailable(imgui_sfml)

# ----------------------------------------------------------------------------
# Dépendance : EnTT (Entity Component System)
# ----------------------------------------------------------------------------
# EnTT est utilisé pour le système ECS du moteur de jeu
message(STATUS "Configuration de EnTT...")

FetchContent_Declare(
    EnTT
    GIT_REPOSITORY https://github.com/skypjack/entt.git
    GIT_TAG v3.15.0
    GIT_SHALLOW TRUE
    GIT_PROGRESS TRUE
)

FetchContent_MakeAvailable(EnTT)

# ----------------------------------------------------------------------------
# Dépendance : nlohmann_json (Bibliothèque JSON pour C++)
# ----------------------------------------------------------------------------
# Utilisé pour la sérialisation/désérialisation des maps et configurations
message(STATUS "Configuration de nlohmann_json...")

FetchContent_Declare(
    nlohmann_json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG v3.11.3
    GIT_SHALLOW TRUE
    GIT_PROGRESS TRUE
)

FetchContent_MakeAvailable(nlohmann_json)

# ----------------------------------------------------------------------------
# Organisation des dépendances externes dans l'IDE
# ----------------------------------------------------------------------------
set_target_properties(
    sfml-system sfml-window sfml-graphics sfml-audio
    PROPERTIES FOLDER "External/SFML"
)

set_target_properties(
    imgui ImGui-SFML
    PROPERTIES FOLDER "External/ImGui"
)

# ----------------------------------------------------------------------------
# Ajout des sous-modules du projet
# ----------------------------------------------------------------------------
# Chaque module possède son propre CMakeLists.txt

# Module Core - Système de base (Application, ResourceManager, etc.)
add_subdirectory(src/core)

# Module Engine - Logique du jeu avec ECS
add_subdirectory(src/engine)

# Module Renderer - Système de rendu graphique
add_subdirectory(src/renderer)

# Module Game - Application de jeu (si activé)
if(BUILD_GAME)
    message(STATUS "Configuration du module Game")
    add_subdirectory(src/game)
endif()

# Module Editor - Éditeur de niveau (si activé)
if(BUILD_EDITOR)
    message(STATUS "Configuration du module Editor")
    add_subdirectory(src/editor)
endif()

# Module Tests - Tests unitaires (si activé)
if(BUILD_TESTS)
    message(STATUS "Configuration des tests")
    enable_testing()
    add_subdirectory(tests)
endif()

# ----------------------------------------------------------------------------
# Copie des ressources dans le dossier de build
# ----------------------------------------------------------------------------
# Cette commande personnalisée copie le dossier resources/ vers le build
add_custom_target(copy_resources ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/resources
        ${CMAKE_BINARY_DIR}/bin/resources
    COMMENT "Copie des ressources dans le dossier de build"
)

# ----------------------------------------------------------------------------
# Résumé de la configuration
# ----------------------------------------------------------------------------
message(STATUS "")
message(STATUS "========================================")
message(STATUS "Configuration PokeMaker")
message(STATUS "========================================")
message(STATUS "Version du projet : ${PROJECT_VERSION}")
message(STATUS "Build type        : ${CMAKE_BUILD_TYPE}")
message(STATUS "Compilateur       : ${CMAKE_CXX_COMPILER_ID}")
message(STATUS "Standard C++      : ${CMAKE_CXX_STANDARD}")
message(STATUS "----------------------------------------")
message(STATUS "Options de build :")
message(STATUS "  BUILD_GAME      : ${BUILD_GAME}")
message(STATUS "  BUILD_EDITOR    : ${BUILD_EDITOR}")
message(STATUS "  BUILD_TESTS     : ${BUILD_TESTS}")
message(STATUS "----------------------------------------")
message(STATUS "Chemins :")
message(STATUS "  Source          : ${CMAKE_SOURCE_DIR}")
message(STATUS "  Build           : ${CMAKE_BINARY_DIR}")
message(STATUS "  Binaires        : ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
message(STATUS "  Ressources      : ${RESOURCES_PATH}")
message(STATUS "========================================")
message(STATUS "")

# cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug -DBUILD_GAME=OFF -DBUILD_EDITOR=ON -DBUILD_TESTS=OFF
# cmake --build build