#include "EditorState.hpp"
#include <iostream>

EditorState::EditorState() : activeProject(nullptr) {}

void EditorState::Init()
{
    // Initialisation des gestionnaires internes
    projectManager = ProjectManager();
    uiManager = UIManager();
    mapEditor = MapEditor();
    camera = Camera();

    activeProject = projectManager.GetCurrentProject();

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

    if (!mapEditor.GetActiveMap() && activeProject)
    {
        mapEditor.NewMap("Base", { 32, 32 }, { 32, 32 }, projectManager);
        Tileset tileset;
        tileset.LoadFromFile("Hills.png");
        mapEditor.GetActiveMap()->SetTileset(&tileset);
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
    uiManager.RenderMainMenu(projectManager);

    // Si un projet est chargé, afficher les panneaux
    if (mapEditor.GetActiveMap() && activeProject)
    {
        // Panel des layers
        uiManager.RenderLayerPanel(mapEditor.GetActiveMap()->GetLayers());
        
        // Sélecteur de tuiles
        uiManager.RenderTileSelector(mapEditor.GetActiveMap()->GetTileset());
    }

    // Gestion des actions de menu (nouveau projet, sauvegarde, etc.)
    uiManager.HandleMenuActions(projectManager);

    // Rendu final ImGui
    ImGui::SFML::Render(window);
}
