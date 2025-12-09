#include "Core/Layer.hpp"
#include <iostream>

namespace Core
{
    bool Layer::AddTile(const Tile& tile)
    {
        m_tiles[tile.m_y * m_width + tile.m_x] = tile;
        return true;
    }

    bool Layer::RemoveTile(unsigned int x, unsigned int y)
    {
        try
        {
            m_tiles[y * m_width + x] = Tile();
            return true;
        }
        catch(...)
        {
            std::cout << "Error tile index out of range..." << std::endl; 
            return false;
        }
        
    }
}