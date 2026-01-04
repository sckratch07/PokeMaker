#ifndef _EDITOR_PANEL_MANAGER_HPP__
#define _EDITOR_PANEL_MANAGER_HPP__

#include "Core/ProjectManager.hpp"
#include "Core/ECS/EntityManager.hpp"
#include <SFML/Window/Event.hpp>

namespace Editor
{
    class PanelManager
    {
    public:
        PanelManager(std::shared_ptr<sf::RenderWindow>& window, std::shared_ptr<Core::ProjectManager>& projectManager, std::shared_ptr<Core::EntityManager>& entityManager)
            : m_window(window), m_projectManager(projectManager), m_entityManager(entityManager) {}

        void handleEvents(const std::optional<sf::Event>& event);

        void update();

    private:
        void docking();

        std::shared_ptr<sf::RenderWindow> m_window;
        std::shared_ptr<Core::ProjectManager> m_projectManager;
        std::shared_ptr<Core::EntityManager> m_entityManager;
    };
}


#endif