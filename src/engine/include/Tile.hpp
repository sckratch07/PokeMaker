#ifndef _ENGINE_TILE_HPP__
#define _ENGINE_TILE_HPP__

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

namespace Engine
{
    // Flags possibles pour un tile
    enum class TileFlag {
        None       = 0,
        Collidable = 1 << 0,
        Damage     = 1 << 1,
        Slow       = 1 << 2,
        Interactable = 1 << 3
    };

    inline TileFlag operator|(TileFlag a, TileFlag b)
    {
        return static_cast<TileFlag>(static_cast<int>(a) | static_cast<int>(b));
    }

    inline bool hasFlag(TileFlag value, TileFlag flag)
    {
        return (static_cast<int>(value) & static_cast<int>(flag)) != 0;
    }

    // Tile de base
    struct Tile {
        int id;                                // ID du tile
        sf::IntRect textureRect;               // Rectangle dans le tileset
        TileFlag flags = TileFlag::None;       // Propriétés
        bool animated = false;
        std::vector<sf::IntRect> frames;       // Frames d'animation
        float frameTime = 0.2f;                // Temps par frame en secondes

        Tile() : id(-1) {}
    };

} // namespace Engine

#endif
