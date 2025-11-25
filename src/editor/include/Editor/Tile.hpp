#ifndef _EDITOR_TILE_HPP__
#define _EDITOR_TILE_HPP__

/**
 * @file Tile.hpp
 * @brief Représente un tile individuel : id, tileset, flags, propriétés, animation.
 */

#include <string>
#include <unordered_map>
#include <cstdint>
#include <vector>

namespace Editor {

/**
 * @enum TileFlags
 * @brief Flags optionnels sur un tile (mask bitwise).
 */
enum TileFlags : uint32_t
{
    TILEFLAG_NONE        = 0,
    TILEFLAG_COLLISION   = 1 << 0,
    TILEFLAG_INTERACTIVE = 1 << 1,
    TILEFLAG_AUTOTILE    = 1 << 2,
    TILEFLAG_ANIMATED    = 1 << 3
};

/**
 * @struct TileAnimationFrame
 * @brief Une frame d'animation pour un tile animé.
 */
struct TileAnimationFrame
{
    uint32_t tileId = 0;  ///< ID du tile dans le tileset
    uint32_t durationMs = 100; ///< durée en millisecondes
};

/**
 * @class Tile
 * @brief Structure représentant un tile individuel dans un layer.
 */
class Tile
{
public:
    Tile() = default;

    /// ID du tile dans son tileset (0 = tile vide)
    uint32_t id = 0;

    /// Nom du tileset source (doit correspondre à un TileSet.name)
    std::string tilesetName;

    /// Flags (collision, interactif, auto-tile, animé…)
    uint32_t flags = TILEFLAG_NONE;

    /// Propriétés utilisateur (ex: “damage=10”, “water=true”)
    std::unordered_map<std::string, std::string> properties;

    // ---- Animation ----
    std::vector<TileAnimationFrame> animationFrames;
    bool IsAnimated() const { return flags & TILEFLAG_ANIMATED; }

    // ---- Auto-tile ----
    // (stockage minimal ; les règles d'autocomposition sont dans AutoTile.hpp / TileMap)
    uint8_t autoTileMask = 0; ///< masque 4/8 directions selon algorithme choisi

    // ---- Utilitaires ----
    inline bool IsEmpty() const { return id == 0; }
    inline bool HasFlag(TileFlags f) const { return (flags & f) != 0; }
    inline void AddFlag(TileFlags f) { flags |= f; }
    inline void RemoveFlag(TileFlags f) { flags &= ~f; }
};

} // namespace Editor

#endif // _EDITOR_TILE_HPP__
