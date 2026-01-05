#ifndef _EDITOR_PANEL_MANAGER_HPP__
#define _EDITOR_PANEL_MANAGER_HPP__

#include "Editor/Panel/MapMenu.hpp"
#include "Core/ProjectManager.hpp"
#include "Core/ECS/EntityManager.hpp"
#include <SFML/Window/Event.hpp>

namespace Editor
{
    class PanelManager
    {
    public:
        PanelManager(sf::RenderWindow& window, std::shared_ptr<Core::ProjectManager>& projectManager, std::shared_ptr<Core::EntityManager>& entityManager)
            : m_window(window), m_projectManager(projectManager), m_entityManager(entityManager),
            m_mapMenu(std::make_unique<PanelMenu::MapMenu>())
        {}

        void handleEvents(const std::optional<sf::Event>& event);

        void update();

    private:
        void docking();

        sf::RenderWindow& m_window;
        std::shared_ptr<Core::ProjectManager> m_projectManager;
        std::shared_ptr<Core::EntityManager> m_entityManager;

        std::unique_ptr<PanelMenu::MapMenu> m_mapMenu;
    };
}

#endif