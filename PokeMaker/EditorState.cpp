#include "EditorState.hpp"
#include <iostream>

EditorState::EditorState() : m_showDemoWindow(false) , m_projectLoaded(false) {}

void EditorState::Init() {
    std::cout << "[EditorState] Initialisation de l'éditeur..." << std::endl;

    // Initialisation de la caméra
    m_camera = Camera({ 640.f, 360.f }, { 1280.f, 720.f });

    // Initialisation de la map par défaut
    m_mapEditor.NewMap("DefaultMap", { 50, 50 }, { 32, 32 });

    // Configuration du projet par défaut (temporaire)
    m_projectManager.CreateProject("ProjetTest", "assets/projects/ProjetTest");

    m_projectLoaded = true;
}

void EditorState::HandleInput(const sf::Event& event) {
    // Si la fenêtre ImGui capture la souris, on ignore les entrées SFML
    if (ImGui::GetIO().WantCaptureMouse)
        return;

    m_camera.HandleInput(event);
}

void EditorState::Update(float dt) {
    // Déplacement / zoom de la caméra
    m_camera.Update(dt);

    // Mise à jour de l'éditeur de carte (tiles, sélection, etc.)
    m_mapEditor.Update(dt);

    // Interface utilisateur
    m_uiManager.RenderMainMenu();

    if (m_projectLoaded) {
        m_uiManager.RenderTileSelector(m_mapEditor.GetActiveTileset());
        m_uiManager.RenderLayerPanel(m_mapEditor.GetLayers());
        m_uiManager.RenderPropertiesPanel(m_mapEditor.GetSelectedTile());
    }

    // Fenêtre de démo ImGui (désactivable)
    if (m_showDemoWindow)
        ImGui::ShowDemoWindow(&m_showDemoWindow);

    // Gère les actions liées au menu
    m_uiManager.HandleMenuActions(m_projectManager);
}

void EditorState::Render(sf::RenderWindow& window) {
    // Appliquer la vue caméra pour afficher la map
    m_camera.Apply(window);

    if (m_projectLoaded) {
        m_mapEditor.Render(window);
    }

    // Revenir à la vue par défaut pour l’interface ImGui
    window.setView(window.getDefaultView());
}
