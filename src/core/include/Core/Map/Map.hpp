#ifndef _CORE_MAP_HPP__
#define _CORE_MAP_HPP__

#include "Core/Map/Layer.hpp"
#include <entt/entt.hpp>
#include <vector>

namespace Core
{
    class EntityManager;

    struct Map
    {
        Map(const std::string& name, unsigned int width, unsigned int height, unsigned int tileWidth, unsigned int tileHeight)
            : m_name(name), m_width(width), m_height(height), m_tileWidth(tileWidth), m_tileHeight(tileHeight) {}
        
        void addLayer(std::string& name) { m_layers.push_back({name, m_width * m_height}); }
        void addEntity(entt::entity entity) { m_entities.push_back(entity); }
        void addTileToLayer(entt::entity tile, unsigned int layerIndex, unsigned int x, unsigned int y)
        {
            if (layerIndex >= m_layers.size()) return;
            unsigned int index = y * m_width + x;
            if (index >= m_layers[layerIndex].m_tiles.size()) return;
            m_layers[layerIndex].m_tiles[index] = Tile(tile);
        }

        void deleteLayer(unsigned int layerIndex, std::shared_ptr<EntityManager>& manager);
        void deleteEntity(unsigned int index, std::shared_ptr<EntityManager>& manager);
        void deleteTileFromLayer(unsigned int layerIndex, unsigned int x, unsigned int y, std::shared_ptr<EntityManager>& manager);
        
        unsigned int m_width = 0;
        unsigned int m_height = 0;

        unsigned int m_tileWidth = 0;
        unsigned int m_tileHeight = 0;

        std::string m_name;
        std::vector<Layer> m_layers;
        std::vector<entt::entity> m_entities;
    };
}

#endif