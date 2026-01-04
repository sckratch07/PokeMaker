#ifndef _CORE_TILESET_HPP__
#define _CORE_TILESET_HPP__

#include "Core/Texture.hpp"

namespace Core
{
    struct Tileset
    {
        Tileset(std::shared_ptr<Texture> texture, sf::Vector2i tileSize)
            : m_texture(texture), m_tileSize(tileSize) {}

        sf::IntRect tileById(unsigned int id) const
        {
            unsigned int tilesPerRow = m_texture->m_textSize.x / static_cast<unsigned int>(m_tileSize.x);
            unsigned int tu = id % tilesPerRow;
            unsigned int tv = id / tilesPerRow;

            return sf::IntRect({tu * m_tileSize.x, tv * m_tileSize.y}, {m_tileSize.x, m_tileSize.y});
        }

        std::shared_ptr<Texture> m_texture;
        sf::Vector2i m_tileSize = {0, 0};
        unsigned int m_maxIndex = 0;
    };
}

#endif