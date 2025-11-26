#include "Editor/EditorApp.hpp"

#include <iostream>
#include <chrono>

namespace Editor {

EditorApp::EditorApp(unsigned int width, unsigned int height, const std::string& title)
    : m_window(sf::VideoMode(sf::Vector2u(width, height)), title, sf::Style::Default),
    m_project(std::make_unique<Project::ProjectManager>()),
    m_ui(std::make_unique<EditorUI>())
{
    m_window.setVerticalSyncEnabled(true);
    m_window.setFramerateLimit(120); // limite soft, on utilise vsync si possible

    // Initialiser ImGui-SFML — doit être fait après la création de la fenêtre
    initImGui();

    // Permettre à l'UI de s'initialiser avec la fenêtre si nécessaire
    m_ui->Initialize(m_window, *m_project);

    // Lancement de la boucle
    m_running = true;
}

EditorApp::~EditorApp()
{
    // Shutdown propre
    if (m_ui) {
        // Permettre à l'UI de libérer ses ressources
        m_ui->Shutdown();
    }
    shutdownImGui();
    if (m_window.isOpen()) m_window.close();
}

void EditorApp::initWindow(unsigned int width, unsigned int height, const std::string& title)
{
    
}

void EditorApp::initImGui()
{
    // Init back-end ImGui-SFML
    if (ImGui::SFML::Init(m_window))
    {
        // Initialise ImGui-SFML (assume imgui and ImGui-SFML fournis par CMake)
        ImGui::CreateContext();

        // Config Docking & Viewports
        ImGuiStyle& style = ImGui::GetStyle();

        // === COULEURS PRINCIPALES ===
        style.Colors[ImGuiCol_Text] = ImVec4(0.95f, 0.96f, 0.98f, 1.00f);
        style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.55f, 0.60f, 1.00f);
        style.Colors[ImGuiCol_WindowBg] = ImVec4(0.10f, 0.12f, 0.15f, 1.00f);
        style.Colors[ImGuiCol_ChildBg] = ImVec4(0.10f, 0.12f, 0.15f, 0.00f);
        style.Colors[ImGuiCol_PopupBg] = ImVec4(0.12f, 0.14f, 0.18f, 0.95f);
        style.Colors[ImGuiCol_Border] = ImVec4(0.25f, 0.30f, 0.45f, 0.50f);
        style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);

        style.Colors[ImGuiCol_FrameBg] = ImVec4(0.20f, 0.25f, 0.35f, 1.00f);
        style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.25f, 0.35f, 0.50f, 1.00f);
        style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.30f, 0.45f, 0.65f, 1.00f);

        style.Colors[ImGuiCol_TitleBg] = ImVec4(0.12f, 0.15f, 0.20f, 1.00f);
        style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.18f, 0.25f, 0.35f, 1.00f);
        style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.10f, 0.12f, 0.15f, 0.75f);

        style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.13f, 0.16f, 0.22f, 1.00f);
        style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.10f, 0.12f, 0.15f, 1.00f);
        style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.25f, 0.35f, 0.50f, 1.00f);
        style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.30f, 0.45f, 0.65f, 1.00f);
        style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.35f, 0.50f, 0.75f, 1.00f);

        style.Colors[ImGuiCol_CheckMark] = ImVec4(0.35f, 0.55f, 1.00f, 1.00f);
        style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.30f, 0.50f, 1.00f, 1.00f);
        style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.35f, 0.55f, 1.00f, 1.00f);

        style.Colors[ImGuiCol_Button] = ImVec4(0.20f, 0.35f, 0.55f, 0.80f);
        style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.30f, 0.50f, 0.85f, 1.00f);
        style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.20f, 0.40f, 0.75f, 1.00f);

        style.Colors[ImGuiCol_Header] = ImVec4(0.20f, 0.35f, 0.55f, 0.80f);
        style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.30f, 0.50f, 0.85f, 1.00f);
        style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.35f, 0.55f, 1.00f, 1.00f);

        style.Colors[ImGuiCol_Separator] = ImVec4(0.28f, 0.35f, 0.50f, 0.60f);
        style.Colors[ImGuiCol_SeparatorHovered] = ImVec4(0.35f, 0.55f, 0.90f, 1.00f);
        style.Colors[ImGuiCol_SeparatorActive] = ImVec4(0.40f, 0.65f, 1.00f, 1.00f);

        style.Colors[ImGuiCol_ResizeGrip] = ImVec4(0.26f, 0.46f, 0.98f, 0.25f);
        style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.26f, 0.46f, 0.98f, 0.70f);
        style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.26f, 0.46f, 0.98f, 0.95f);

        style.Colors[ImGuiCol_Tab] = ImVec4(0.20f, 0.35f, 0.55f, 0.80f);
        style.Colors[ImGuiCol_TabHovered] = ImVec4(0.30f, 0.50f, 0.85f, 1.00f);
        style.Colors[ImGuiCol_TabActive] = ImVec4(0.35f, 0.55f, 1.00f, 1.00f);
        style.Colors[ImGuiCol_TabUnfocused] = ImVec4(0.15f, 0.20f, 0.30f, 0.90f);
        style.Colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.20f, 0.35f, 0.55f, 1.00f);

        style.Colors[ImGuiCol_DockingPreview] = ImVec4(0.26f, 0.46f, 0.98f, 0.70f);
        style.Colors[ImGuiCol_DockingEmptyBg] = ImVec4(0.15f, 0.18f, 0.22f, 1.00f);

        style.Colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
        style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
        style.Colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
        style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);

        style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.30f, 0.50f, 0.85f, 0.35f);
        style.Colors[ImGuiCol_DragDropTarget] = ImVec4(0.26f, 0.46f, 0.98f, 0.95f);

        style.Colors[ImGuiCol_NavHighlight] = ImVec4(0.26f, 0.46f, 0.98f, 1.00f);
        style.Colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
        style.Colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
        style.Colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.10f, 0.10f, 0.10f, 0.60f);

        // === STYLE ===
        style.WindowRounding = 6.0f;
        style.FrameRounding = 4.0f;
        style.GrabRounding = 4.0f;
        style.ScrollbarRounding = 6.0f;
        style.TabRounding = 4.0f;
        style.WindowPadding = ImVec2(8.0f, 8.0f);
        style.FramePadding = ImVec2(5.0f, 3.0f);
        style.ItemSpacing = ImVec2(6.0f, 4.0f);
        style.IndentSpacing = 20.0f;
        style.ScrollbarSize = 16.0f;

        // === CONFIG ===
        ImGuiIO& io = ImGui::GetIO(); 
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
    }
}

void EditorApp::shutdownImGui()
{
    // Dé-init ImGui-SFML
    ImGui::SFML::Shutdown();
    ImGui::DestroyContext();
}

void EditorApp::Run()
{
    // Horloge pour le delta time
    m_deltaClock.restart();

    while (m_running && m_window.isOpen())
    {
        processEvents();

        // Calcul du delta time
        sf::Time dt = m_deltaClock.restart();
        float dtSeconds = dt.asSeconds();

        // Mise à jour ImGui-SFML (synchronise input, etc.)
        ImGui::SFML::Update(m_window, dt);

        update(dtSeconds);
        render();
    }
}

void EditorApp::processEvents()
{
    while (const std::optional<sf::Event>& event = m_window.pollEvent())
    {
        // Toujours envoyer l'event à ImGui-SFML
        ImGui::SFML::ProcessEvent(m_window, *event);

        if (event->is<sf::Event::Closed>()) Quit();
        
        if (event->is<sf::Event::KeyPressed>()) handleShortcuts(*event);

        // Laisser l'UI traitée l'event (sélection, clic, drag, etc.)
        if (m_ui) {
            m_ui->ProcessEvent(*event);
        }
    }
}

void EditorApp::handleShortcuts(const sf::Event& event)
{
    // Gérer Ctrl+O (ouvrir), Ctrl+S (sauver), Ctrl+Shift+S (sauver sous), Ctrl+Q (quitter)
    const sf::Event::KeyPressed* keyPressed = event.getIf<sf::Event::KeyPressed>();

    bool ctrl = keyPressed->control;
    bool shift = keyPressed->shift;

    if (!ctrl) return; // tous nos raccourcis sont Ctrl+...

    if (keyPressed->code == sf::Keyboard::Key::O)
    {
        // Open project
        if (m_ui) m_ui->OnOpenProject();
    }
    else if (keyPressed->code == sf::Keyboard::Key::S)
    {
        if (shift) {
            // Save As
            if (m_ui) m_ui->OnSaveProjectAs();
        } else {
            // Save
            if (m_ui) m_ui->OnSaveProject();
        }
    }
    else if (keyPressed->code == sf::Keyboard::Key::Q)
    {
        Quit();
    }
}

void EditorApp::update(float dt)
{
    // Update du manager de projet si nécessaire
    if (m_project) {
        m_project->Update(dt);
    }

    // Update de l'UI (le UI gère panels, outils, éditeurs, etc.)
    if (m_ui) {
        m_ui->Update(dt);
    }
}

void EditorApp::render()
{
    // Nettoyage de la fenêtre
    m_window.clear(m_clearColor);

    // Rendu spécifique : si le renderer intégré doit dessiner des things via SFML,
    // l'UI peut s'en charger ou le Renderer du module Renderer.
    // Ici l'UI sera responsable d'appeler ses propres couches de rendu (map preview, etc.)
    if (m_ui) {
        m_ui->Render(m_window);
    }

    // Render ImGui (ImGui::SFML::Render utilise le contexte SFML)
    ImGui::SFML::Render(m_window);

    // Si Viewports multipless sont activés, ImGui::UpdatePlatformWindows() etc. sont gérés par ImGui-SFML
    m_window.display();
}

void EditorApp::Quit()
{
    m_running = false;
    // On ferme la fenêtre ; la boucle principale se terminera proprement.
    if (m_window.isOpen()) {
        m_window.close();
    }
}

} // namespace Editor
