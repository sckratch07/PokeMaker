#pragma once
#include <ImGui/imgui.h>
#include <ImGui/imgui-SFML.h>

#include "ProjectManager.hpp"
#include "MapEditor.hpp"
#include "Camera.hpp"

class EditorState {
public:
    EditorState();

    void CloseEditor();

    void Init();                                           // Initialisation complète
    void HandleEvent(std::optional<sf::Event>& evant);     // Gestion des évènement
    void Update(float dt, sf::RenderWindow& window);       // Mise à jour logique
    void Render(sf::RenderWindow& window);                 // Rendu global

    // ImGui Render
    void RenderMainMenu();
    void RenderTileSelector();
    void RenderLayerPanel();
    void RenderProjectPanel();

private:
    ProjectManager projectManager;                         // Gestion de projet
    MapEditor mapEditor;                                   // Éditeur de carte
    Camera camera;                                         // Caméra
    Project* activeProject;                                // Projet actif (ou nullptr)
    ImVec2 windowCenter;
    bool placeMode;

    // Widget boolean
    bool showTileSelector = true;
    bool showLayersPanel = true;
    bool showProjectPanel = true;

    // Selector
    int selectedTileID;
    int selectedLayer;
    int selectedMap;
    int selectedTilesetIndex;
    int selectedLinkMap;

    // Create Value
    int tileSize[2];
    int mapSize[2];
    int enterPos[2];
    int exitPos[2];
    char name[50];
    std::string selectetExitMap;
    float actionDistance;

    bool createProjectPopupOpen = false;
};

