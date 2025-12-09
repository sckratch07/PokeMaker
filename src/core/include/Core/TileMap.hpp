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
        TileMap(const char* name, unsigned int mapSize[2], unsigned int tileSize[2]) :
            m_name(name), m_width(mapSize[0]), m_height(mapSize[1]),
            m_tileWidth(tileSize[0]), m_tileHeight(tileSize[1]) {}

        bool AddLayer(const char* layerName);
        bool RemoveLayer(const std::string layerName);

        std::string m_name;

        unsigned int m_width = 0;
        unsigned int m_height = 0;

        unsigned int m_tileWidth = 0;
        unsigned int m_tileHeight = 0;

        std::vector<Layer> m_layers;
    };
}

#endif