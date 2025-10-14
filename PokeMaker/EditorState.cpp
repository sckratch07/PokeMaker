#include "EditorState.hpp"
#include <iostream>

EditorState::EditorState() : activeProject(nullptr) {}

void EditorState::Init()
{
    // Initialisation des gestionnaires internes
    projectManager = ProjectManager();
    //uiManager = UIManager();
    mapEditor = MapEditor(projectManager);
    camera = Camera();

    std::cout << "[EditorState] Initialise." << std::endl;
}

void EditorState::HandleEvent(std::optional<sf::Event>& event)
{
    camera.HandleEvent(event);
}

void EditorState::Update(float dt)
{
    camera.Move(dt);

    mapEditor.Update(dt);

    // Si un projet est actif, on peut aussi mettre à jour ses données
    if (activeProject) {
        // exemple : mise à jour d’un aperçu ou d’une mini-map
    }
}

void EditorState::Render(sf::RenderWindow& window)
{
    // Appliquer la vue de la caméra
    camera.Apply(window);

    // Rendu de la carte active
    mapEditor.Render(window);

    // Revenir à la vue par défaut pour les interfaces
    window.setView(window.getDefaultView());

    // Interface ImGui
    //uiManager.RenderMainMenu();

    // Si un projet est chargé, afficher les panneaux
    if (activeProject) {
        // Sélecteur de tuiles
        // (MapEditor pourrait exposer un Tileset ou tuile active)
        // Exemple : uiManager.RenderTileSelector(activeProject->GetTileset());
    }
    // Gestion des actions de menu (nouveau projet, sauvegarde, etc.)
    //uiManager.HandleMenuActions(projectManager);

    // Rendu final ImGui
    ImGui::SFML::Render(window);
}
