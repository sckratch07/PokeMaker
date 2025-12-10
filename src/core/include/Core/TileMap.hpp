#ifndef _CORE_TILEMAP_HPP__
#define _CORE_TILEMAP_HPP__

#include "Core/Layer.hpp"

#include <string>
#include <vector>

namespace Core
{
    struct TileMap
    {
        TileMap() = default;
        TileMap(const char* name, unsigned int mapWidth, unsigned int mapHeight, unsigned int tileWidth, unsigned int tileHeight) :
            m_name(name), m_width(mapWidth), m_height(mapHeight),
            m_tileWidth(tileWidth), m_tileHeight(tileHeight) {}

        bool AddLayer(const char* layerName);
        bool RemoveLayer(const std::string layerName);

        std::string m_name = "Unnamed Map";

        unsigned int m_width = 0;
        unsigned int m_height = 0;

        unsigned int m_tileWidth = 0;
        unsigned int m_tileHeight = 0;

        std::vector<Layer> m_layers;
    };
}

#endif