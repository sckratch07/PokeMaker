/**
 * @file EditorApplication.cpp
 * @brief Implémentation d'EditorApplication.
 *
 * Note : l'include d'ImGui-SFML peut varier selon comment tu as installé la binding.
 * Ici j'utilise la forme <imgui-SFML.h> ; si ton projet l'expose différemment adapte-le.
 */

#include "Editor/EditorApplication.hpp"

#include <iostream>

namespace Editor {

EditorApplication::EditorApplication()
    : m_running(false)
{
}

EditorApplication::~EditorApplication()
{
    // Shutdown propre
    if (ImGui::GetCurrentContext()) {
        ImGui::SFML::Shutdown();
    }
    if (m_window.isOpen()) {
        m_window.close();
    }
}

bool EditorApplication::Init(const sf::Vector2u& windowSize,
                             const std::string& title,
                             const std::string& resourcesPath)
{
    m_resourcesPath = resourcesPath;

    // Création fenêtre SFML
    sf::VideoMode vm(windowSize.x, windowSize.y);
    m_window.create(vm, title, sf::Style::Default);
    m_window.setVerticalSyncEnabled(true);

    // Initialisation ImGui-SFML
    try {
        if (!ImGui::SFML::Init(m_window)) {
            std::cerr << "[EditorApplication] Erreur : ImGui-SFML init failed\n";
            return false;
        }
    } catch (const std::exception& e) {
        std::cerr << "[EditorApplication] Exception during ImGui-SFML Init: " << e.what() << "\n";
        return false;
    }

    // Setup style
    SetupImGuiStyle();

    // Instancier les sous-systèmes
    m_resourceCache   = std::make_unique<ResourceCache>(m_resourcesPath);
    m_projectManager  = std::make_unique<ProjectManager>(m_resourceCache.get());
    m_viewController  = std::make_unique<ViewController>(m_window); // peut prendre window ref
    m_gridRenderer    = std::make_unique<GridRenderer>(m_viewController.get());
    m_tilePalette     = std::make_unique<TilePalette>(m_resourceCache.get());
    m_layerManager    = std::make_unique<LayerManager>();

    // Charger ressources par défaut (tilesets par défaut, shaders, etc.)
    LoadDefaultResources();

    // reset clock
    m_deltaClock.restart();
    m_running = true;

    return true;
}

void EditorApplication::Run()
{
    while (m_running && m_window.isOpen())
    {
        ProcessEvents();

        sf::Time dt = m_deltaClock.restart();
        Update(dt);

        Render();
    }
}

void EditorApplication::Quit()
{
    m_running = false;
}

// --- événements, update, render ---

void EditorApplication::ProcessEvents()
{
    sf::Event event;
    while (m_window.pollEvent(event))
    {
        // ImGui-SFML doit traiter l'événement avant l'application
        ImGui::SFML::ProcessEvent(event);

        if (event.type == sf::Event::Closed)
        {
            Quit();
        }

        // déléguer à ViewController (ex: navigation avec souris, drag)
        if (m_viewController)
            m_viewController->HandleEvent(event);

        // TODO: déléguer aux outils (brush/select/fill) si besoin :
        // if (m_currentTool) m_currentTool->HandleEvent(event);
    }
}

void EditorApplication::Update(sf::Time dt)
{
    // Mettre à jour ImGui (nécessaire pour ImGui-SFML)
    ImGui::SFML::Update(m_window, dt);

    // Update sous-systèmes
    if (m_projectManager) m_projectManager->Update(dt);
    if (m_viewController) m_viewController->Update(dt);
    if (m_gridRenderer) m_gridRenderer->Update(dt);
    if (m_tilePalette) m_tilePalette->Update(dt);
    if (m_layerManager) m_layerManager->Update(dt);

    // Exemple: afficher un menu simple (peut être déplacé dans EditorUI)
    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::MenuItem("New Project")) {
                m_projectManager->CreateNewProject();
            }
            if (ImGui::MenuItem("Open Project")) {
                m_projectManager->OpenProjectDialog();
            }
            if (ImGui::MenuItem("Save Project")) {
                m_projectManager->SaveCurrentProject();
            }
            if (ImGui::MenuItem("Exit")) {
                Quit();
            }
            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("View"))
        {
            if (ImGui::MenuItem("Toggle Grid")) {
                m_gridRenderer->ToggleVisible();
            }
            ImGui::EndMenu();
        }

        ImGui::EndMainMenuBar();
    }

    // UI panels (palette, layer manager...) - each draws its own ImGui windows
    if (m_tilePalette) m_tilePalette->RenderUI();
    if (m_layerManager) m_layerManager->RenderUI();
    if (m_projectManager) m_projectManager->RenderUI();
}

void EditorApplication::Render()
{
    m_window.clear(sf::Color(50, 50, 60));

    // Appliquer view camera contrôlée par ViewController
    if (m_viewController) m_viewController->ApplyView(m_window);

    // Rendu des éléments de la scène : TileMap, layers, NPCs, etc.
    // Ici on se contente d'appeler les renderers existants
    // (Le TileMapRenderer / GridRenderer etc. doivent être implémentés ailleurs)
    if (m_gridRenderer) m_gridRenderer->Render(m_window);

    // Remettre vue par défaut pour UI si nécessaire
    m_window.setView(m_window.getDefaultView());

    // Rendu ImGui
    ImGui::SFML::Render(m_window);

    m_window.display();
}

// --- helpers ---

void EditorApplication::SetupImGuiStyle()
{
    ImGuiStyle& style = ImGui::GetStyle();
    style.WindowRounding = 6.0f;
    style.FrameRounding = 4.0f;
    style.GrabRounding = 4.0f;
    style.ScrollbarRounding = 6.0f;
    // autres réglages ergonomiques par défaut...
}

void EditorApplication::LoadDefaultResources()
{
    // Charger quelques ressources par défaut (tilesets, shaders...) via ResourceCache.
    // ResourceCache est responsable de gérer chemins de resources et cache.
    if (m_resourceCache) {
        // noms d'exemples - adapter selon tes fichiers
        m_resourceCache->LoadTexture("default_tileset", m_resourcesPath + "/tiles/default_tileset.png");
        m_resourceCache->LoadShader("default_map_shader", m_resourcesPath + "/shaders/map_default.frag");
    }
}

} // namespace Editor
