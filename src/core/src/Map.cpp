#include "Core/Map/Map.hpp"
#include "Core/ECS/EntityManager.hpp"

namespace Core
{
    void Map::deleteLayer(unsigned int layerIndex, std::shared_ptr<EntityManager>& manager)
    {
        if (layerIndex >= m_layers.size()) return;

        for (int i = 0; i < m_layers[layerIndex].m_tiles.size(); i++)
        {
            if (m_layers[layerIndex].m_tiles[i].m_id != entt::null)
                manager->destroyEntity(m_layers[layerIndex].m_tiles[i].m_id);
        }

        for (unsigned int i = layerIndex; i < m_layers.size() - 2; i++)
        {
            std::swap(m_layers[i], m_layers[i + 1]);
        }

        m_layers.pop_back();
    }

    void Map::deleteEntity(unsigned int index, std::shared_ptr<EntityManager>& manager)
    {
        manager->destroyEntity(m_entities[index]);
        std::swap(m_entities[index], m_entities.back());
        m_entities.pop_back();
    }

    void Map::deleteTileFromLayer(unsigned int layerIndex, unsigned int x, unsigned int y, std::shared_ptr<EntityManager>& manager)
    {
        if (layerIndex >= m_layers.size()) return;

        unsigned int index = y * m_width + x;
        if (index >= m_layers[layerIndex].m_tiles.size()) return;

        if (m_layers[layerIndex].m_tiles[index].m_id != entt::null) manager->destroyEntity(m_layers[layerIndex].m_tiles[index].m_id);
        m_layers[layerIndex].m_tiles[index] = Tile();
    }
}