#ifndef _CORE_TILE_HPP__
#define _CORE_TILE_HPP__

#include <entt/entt.hpp>

namespace Core
{
    struct Tile
    {
        Tile() = default;
        Tile(entt::entity id) : m_id(id) {}

        entt::entity m_id = entt::null;
    };
}

#endif