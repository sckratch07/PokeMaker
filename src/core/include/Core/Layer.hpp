#ifndef _CORE_LAYER_HPP__
#define _CORE_LAYER_HPP__

#include "Core/Tile.hpp"

#include <string>
#include <vector>

namespace Core
{
    struct Layer
    {
        Layer() = default;
        Layer(const char* name, unsigned int width, unsigned int height) :
            m_name(name), m_width(width), m_height(height)
        {
            m_tiles.resize(width * height);
        }

        bool AddTile(const Tile& tile);
        bool RemoveTile(unsigned int x, unsigned int y);

        std::string m_name;

        unsigned int m_width = 0;
        unsigned int m_height = 0;

        std::vector<Tile> m_tiles;
    };
}

#endif