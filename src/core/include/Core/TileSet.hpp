#ifndef _CORE_TILESET_HPP__
#define _CORE_TILESET_HPP__

#include <string>

namespace Core
{
    struct Tileset
    {
        Tileset() = default;
        Tileset(const std::string& name, const std::string& imagePath, unsigned int tileSize[2])
            : m_name(name), m_imagePath(imagePath), m_tileWidth(tileSize[0]), m_tileHeight(tileSize[1]) {}

        std::string m_name;
        std::string m_imagePath;

        unsigned int m_tileWidth;
        unsigned int m_tileHeight;
    };
}

#endif