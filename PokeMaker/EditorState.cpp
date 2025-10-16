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

    mapEditor.NewMap("DefaultMap", { 32, 18 }, { 32, 32 }, projectManager);
    mapEditor.LoadTileset("Hills.png", { 32, 32 });

    std::cout << "[EditorState] Initialise." << std::endl;
}

void EditorState::HandleEvent(std::optional<sf::Event>& event)
{
    camera.HandleEvent(event);
}

void EditorState::Update(float dt, sf::RenderWindow& window)
{
    camera.Move(dt);
    mapEditor.Update(dt, window, uiManager, camera);
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

    // Si une map est chargée, afficher les widgets
    if (mapEditor.GetActiveMap())
        uiManager.RenderLayerPanel(mapEditor.GetActiveMap()->GetLayers());
    if (mapEditor.GetTileset())
        uiManager.RenderTileSelector(*mapEditor.GetTileset());

    uiManager.RenderPropertiesPanel(nullptr);

    // Gestion des actions de menu (nouveau projet, sauvegarde, etc.)
    uiManager.HandleMenuActions(projectManager);

    // Rendu final ImGui
    ImGui::SFML::Render(window);
}
