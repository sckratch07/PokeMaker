#include "App.hpp"

App::App() : window(sf::VideoMode(sf::Vector2u(1280, 720)), "PokeMaker"), /*editorState(),*/ isRunning(true)
{
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(60);

    if (ImGui::SFML::Init(window))
    {
        ImGuiStyle& guiStyle = ImGui::GetStyle();
        guiStyle.Colors[ImGuiCol_WindowBg] = ImVec4(0.18f, 0.18f, 0.22f, 1.f);
        guiStyle.Colors[ImGuiCol_Tab] = ImVec4(0.23f, 0.24f, 0.34f, 1.f);
        guiStyle.Colors[ImGuiCol_TabActive] = ImVec4(0.38f, 0.38f, 0.56f, 1.f);
        guiStyle.Colors[ImGuiCol_ChildBg] = ImVec4(0.23f, 0.23f, 0.27f, 1.f);
        guiStyle.Colors[ImGuiCol_FrameBg] = ImVec4(0.28f, 0.28f, 0.37f, 1.f);
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
    window.clear(sf::Color(50, 50, 50)); // couleur de fond neutre

    // Appliquer la camera / view si EditorState s'en occupe avant de dessiner
    editorState.Render(window);

    window.display();
}
