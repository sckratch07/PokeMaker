#pragma once
#include <SFML/Graphics.hpp>
#include <ImGui/imgui.h>
#include <ImGui/imgui-SFML.h>

#include "UIManager.hpp"
#include "ProjectManager.hpp"
#include "MapEditor.hpp"
#include "Camera.hpp"
#include "Project.hpp"

class EditorState {
public:
    EditorState();

    void Init();                                           // Initialisation complète
    void HandleEvent(std::optional<sf::Event>& evant);     // Gestion des évènement
    void Update(float dt, sf::RenderWindow& window);       // Mise à jour logique
    void Render(sf::RenderWindow& window);                 // Rendu global

private:
    UIManager uiManager;                                   // Interface utilisateur (ImGui)
    ProjectManager projectManager;                         // Gestion de projet
    MapEditor mapEditor;                                   // Éditeur de carte
    Camera camera;                                         // Caméra
    Project* activeProject;                                // Projet actif (ou nullptr)
};

