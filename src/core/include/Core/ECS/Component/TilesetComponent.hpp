#ifndef _CORE_TILESET_COMPONENT_HPP__
#define _CORE_TILESET_COMPONENT_HPP__

#include "Core/Tileset.hpp"

namespace Core
{
    struct TilesetComponent
    {
        TilesetComponent() = default;
        explicit TilesetComponent(std::shared_ptr<Tileset> tileset) : m_tileset(tileset) {}

        std::shared_ptr<Tileset> m_tileset = nullptr;
    };
}

#endif