#ifndef _EDITOR_MAP_MENU_HPP__
#define _EDITOR_MAP_MENU_HPP__

#include "Core/ProjectManager.hpp"
#include "Core/ECS/EntityManager.hpp"
#include <SFML/Graphics.hpp>

namespace Editor::PanelMenu
{
    class MapMenu
    {
    public:
        MapMenu(std::shared_ptr<Core::EntityManager>& entityManger) : m_entityManager(entityManger), m_currentMap(nullptr), m_tileSelected(0), m_layerSelected(0) {}
        ~MapMenu() = default;
        
        void handleEvents(const std::optional<sf::Event>& event);

        void update(std::shared_ptr<Core::ProjectManager>& projectManager);
    
    private:
        void mapSelector(std::shared_ptr<Core::ProjectManager>& projectManager);
        void mapManage();
        void tilesetSelector();
        void tilePropriety();

        Core::Map* m_currentMap;
        std::shared_ptr<Core::EntityManager> m_entityManager;

        unsigned int m_tileSelected;
        unsigned int m_layerSelected;

        char m_bufferMapName[50] = "Default";
        int m_bufferMapSize[2] = {10, 10};
        int m_bufferTileSize[2] = {32, 32};
    };
}

#endif