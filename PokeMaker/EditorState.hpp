#pragma once
#include <ImGui/imgui.h>
#include <ImGui/imgui-SFML.h>

#include "ProjectManager.hpp"
#include "MapEditor.hpp"
#include "Camera.hpp"

class EditorState {
public:
    EditorState();

    void Init();                                           // Initialisation complète
    void HandleEvent(std::optional<sf::Event>& evant);     // Gestion des évènement
    void Update(float dt, sf::RenderWindow& window);       // Mise à jour logique
    void Render(sf::RenderWindow& window);                 // Rendu global

    // ImGui Render
    void RenderMainMenu();
    void RenderTileSelector();
    void RenderLayerPanel();

private:
    ProjectManager projectManager;                         // Gestion de projet
    MapEditor mapEditor;                                   // Éditeur de carte
    Camera camera;                                         // Caméra
    Project* activeProject;                                // Projet actif (ou nullptr)

    bool showTileSelector = true;
    bool showLayersPanel = true;

    int selectedTileID;
    int selectedLayer;

    int tileSize[2];

    bool createProjectPopupOpen = false;
};

