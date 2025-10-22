#include "App.hpp"

App::App() : window(sf::VideoMode(sf::Vector2u(1280, 720)), "PokeMaker"), /*editorState(),*/ isRunning(true)
{
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(60);

    if (ImGui::SFML::Init(window))
    {
        ImGuiStyle& style = ImGui::GetStyle();
        ImVec4* colors = style.Colors;

        // === COULEURS PRINCIPALES ===
        colors[ImGuiCol_Text] = ImVec4(0.95f, 0.96f, 0.98f, 1.00f);
        colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.55f, 0.60f, 1.00f);
        colors[ImGuiCol_WindowBg] = ImVec4(0.10f, 0.12f, 0.15f, 1.00f);
        colors[ImGuiCol_ChildBg] = ImVec4(0.10f, 0.12f, 0.15f, 0.00f);
        colors[ImGuiCol_PopupBg] = ImVec4(0.12f, 0.14f, 0.18f, 0.95f);
        colors[ImGuiCol_Border] = ImVec4(0.25f, 0.30f, 0.45f, 0.50f);
        colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);

        colors[ImGuiCol_FrameBg] = ImVec4(0.20f, 0.25f, 0.35f, 1.00f);
        colors[ImGuiCol_FrameBgHovered] = ImVec4(0.25f, 0.35f, 0.50f, 1.00f);
        colors[ImGuiCol_FrameBgActive] = ImVec4(0.30f, 0.45f, 0.65f, 1.00f);

        colors[ImGuiCol_TitleBg] = ImVec4(0.12f, 0.15f, 0.20f, 1.00f);
        colors[ImGuiCol_TitleBgActive] = ImVec4(0.18f, 0.25f, 0.35f, 1.00f);
        colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.10f, 0.12f, 0.15f, 0.75f);

        colors[ImGuiCol_MenuBarBg] = ImVec4(0.13f, 0.16f, 0.22f, 1.00f);
        colors[ImGuiCol_ScrollbarBg] = ImVec4(0.10f, 0.12f, 0.15f, 1.00f);
        colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.25f, 0.35f, 0.50f, 1.00f);
        colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.30f, 0.45f, 0.65f, 1.00f);
        colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.35f, 0.50f, 0.75f, 1.00f);

        colors[ImGuiCol_CheckMark] = ImVec4(0.35f, 0.55f, 1.00f, 1.00f);
        colors[ImGuiCol_SliderGrab] = ImVec4(0.30f, 0.50f, 1.00f, 1.00f);
        colors[ImGuiCol_SliderGrabActive] = ImVec4(0.35f, 0.55f, 1.00f, 1.00f);

        colors[ImGuiCol_Button] = ImVec4(0.20f, 0.35f, 0.55f, 0.80f);
        colors[ImGuiCol_ButtonHovered] = ImVec4(0.30f, 0.50f, 0.85f, 1.00f);
        colors[ImGuiCol_ButtonActive] = ImVec4(0.20f, 0.40f, 0.75f, 1.00f);

        colors[ImGuiCol_Header] = ImVec4(0.20f, 0.35f, 0.55f, 0.80f);
        colors[ImGuiCol_HeaderHovered] = ImVec4(0.30f, 0.50f, 0.85f, 1.00f);
        colors[ImGuiCol_HeaderActive] = ImVec4(0.35f, 0.55f, 1.00f, 1.00f);

        colors[ImGuiCol_Separator] = ImVec4(0.28f, 0.35f, 0.50f, 0.60f);
        colors[ImGuiCol_SeparatorHovered] = ImVec4(0.35f, 0.55f, 0.90f, 1.00f);
        colors[ImGuiCol_SeparatorActive] = ImVec4(0.40f, 0.65f, 1.00f, 1.00f);

        colors[ImGuiCol_ResizeGrip] = ImVec4(0.26f, 0.46f, 0.98f, 0.25f);
        colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.26f, 0.46f, 0.98f, 0.70f);
        colors[ImGuiCol_ResizeGripActive] = ImVec4(0.26f, 0.46f, 0.98f, 0.95f);

        colors[ImGuiCol_Tab] = ImVec4(0.20f, 0.35f, 0.55f, 0.80f);
        colors[ImGuiCol_TabHovered] = ImVec4(0.30f, 0.50f, 0.85f, 1.00f);
        colors[ImGuiCol_TabActive] = ImVec4(0.35f, 0.55f, 1.00f, 1.00f);
        colors[ImGuiCol_TabUnfocused] = ImVec4(0.15f, 0.20f, 0.30f, 0.90f);
        colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.20f, 0.35f, 0.55f, 1.00f);

        colors[ImGuiCol_DockingPreview] = ImVec4(0.26f, 0.46f, 0.98f, 0.70f);
        colors[ImGuiCol_DockingEmptyBg] = ImVec4(0.15f, 0.18f, 0.22f, 1.00f);

        colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
        colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
        colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
        colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);

        colors[ImGuiCol_TextSelectedBg] = ImVec4(0.30f, 0.50f, 0.85f, 0.35f);
        colors[ImGuiCol_DragDropTarget] = ImVec4(0.26f, 0.46f, 0.98f, 0.95f);

        colors[ImGuiCol_NavHighlight] = ImVec4(0.26f, 0.46f, 0.98f, 1.00f);
        colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
        colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
        colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.10f, 0.10f, 0.10f, 0.60f);

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
    }

    editorState.Init();
}

App::~App()
{
    ImGui::SFML::Shutdown();
}

void App::Run()
{
    sf::Clock clock;

    while (isRunning && window.isOpen())
    {
        // Calcul du deltaTime
        deltaTime = clock.restart();

        // Gestion des événements
        ProcessEvents();
        // Mise à jour de la logique
        Update(deltaTime);
        // Rendu
        Render();
    }
}

void App::ProcessEvents()
{
    while (std::optional<sf::Event> event = window.pollEvent())
    {
        ImGui::SFML::ProcessEvent(window, *event);

        // Gestion standard : fermeture
        if (event->is<sf::Event::Closed>())
        {
            isRunning = false;
            window.close();
            return;
        }

        // Autres événements (touche, souris, redimensionnement...)
        editorState.HandleEvent(event);
    }
}

void App::Update(sf::Time& dt)
{
    ImGui::SFML::Update(window, dt);

    // Mise à jour de l'état de l'éditeur
    editorState.Update(dt.asSeconds(), window);
}

void App::Render()
{
    window.clear(sf::Color(20, 23, 30)); // couleur de fond neutre

    // Appliquer la camera / view si EditorState s'en occupe avant de dessiner
    editorState.Render(window);

    window.display();
}
