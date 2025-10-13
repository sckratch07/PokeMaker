#include "Application.hpp"
#include <iostream>

Application::Application() : m_window(sf::VideoMode(sf::Vector2u(1280, 720)), "PokeMaker"), m_isRunning(true)
{
    // Initialisation SFML + ImGui
    this->m_window.setFramerateLimit(60);
    if (!ImGui::SFML::Init(this->m_window))
        std::cerr << "Erreur: Échec d'initialisation de ImGui-SFML." << std::endl;

    // Initialisation de l’état principal (éditeur)
    this->m_editorState.Init();
}

Application::~Application()
{
    ImGui::SFML::Shutdown();
}

void Application::Run()
{
    while (this->m_isRunning && this->m_window.isOpen())
    {
        this->ProcessEvents();
        float dt = m_deltaClock.restart().asSeconds();
        Update(dt);
        Render();
    }
}

void Application::ProcessEvents()
{
    while (std::optional<sf::Event> event = m_window.pollEvent()) {
        ImGui::SFML::ProcessEvent(this->m_window, event);

        if (event->is<sf::Event::Closed>())
        {
            m_isRunning = false;
            m_window.close();
        }

        // Passe les événements à l’éditeur (caméra, interactions…)
        m_editorState.HandleInput(event);
    }
}

void Application::Update(float dt) {
    ImGui::SFML::Update(m_window, sf::seconds(dt));

    // Mise à jour de l’éditeur
    m_editorState.Update(dt);
}

void Application::Render() {
    m_window.clear(sf::Color(30, 30, 30));

    // Rendu SFML (tiles, map, etc.)
    m_editorState.Render(m_window);

    // Rendu ImGui
    ImGui::SFML::Render(m_window);

    m_window.display();
}
