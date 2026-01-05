#ifndef _CORE_LAYER_HPP__
#define _CORE_LAYER_HPP__

#include "Core/Map/Tile.hpp"
#include <vector>

namespace Core
{
    struct Layer
    {
        Layer(std::string& name, unsigned int size) : m_name(name)
        {
            m_tiles.resize(size);
        }

        std::string m_name;

        std::vector<Tile> m_tiles;
    };
}

#endif