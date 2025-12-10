#ifndef _CORE_TILE_HPP__
#define _CORE_TILE_HPP__

#include "Core/Tileset.hpp"

#include <string>
#include <vector>

namespace Core
{
    enum TileType
    {
        EMPTY,
        NORMAL,
        ANIMATED,
        INTERACTIVE,
        AUTOTILE
    };

    struct Tile
    {
        Tile() = default;
        Tile(TileType type, unsigned int x, unsigned int y, unsigned int width, unsigned int height, std::shared_ptr<Tileset> tileset, unsigned int tileIndex) :
            m_type(type), m_x(x), m_y(y), m_width(width), m_height(height),
            m_tileset(tileset), m_tileIndex(tileIndex) {}
        virtual ~Tile() = default;

        TileType m_type = EMPTY;
        unsigned int m_x = -1;
        unsigned int m_y = -1;

        std::shared_ptr<Tileset> m_tileset = nullptr;
        unsigned int m_tileIndex = -1;
        unsigned int m_width = 0;
        unsigned int m_height = 0;
    };
}

#endif