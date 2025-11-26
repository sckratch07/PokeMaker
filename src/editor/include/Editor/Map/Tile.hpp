#ifndef _EDITOR_TILE_HPP__
#define _EDITOR_TILE_HPP__

/**
 * @file Tile.hpp
 * @brief Représentation d'une tile simple (id, tileset, propriétés).
 */

#include <string>
#include <unordered_map>

namespace Editor::Project { struct TileSetDescriptor; }

namespace Editor::Map {

/**
 * @struct Tile
 * @brief Représente une tile placée dans une couche (layer).
 *
 * - tilesetName : nom du tileset (doit correspondre à un TileSetDescriptor du Project)
 * - tileIndex : index (0-based) de la tile dans le tileset (ligne-major)
 * - flipX / flipY : flags de retournement
 * - collision : marqueur simple de collision
 * - properties : dictionnaire libre pour attacher des comportements, scripts, etc.
 */
struct Tile
{
    std::string tilesetName;                       ///< référence logique au TileSet
    int tileIndex = -1;                            ///< -1 = vide / aucun tile
    bool flipX = false;
    bool flipY = false;
    bool collision = false;
    std::unordered_map<std::string, std::string> properties;

    Tile() = default;
    Tile(const std::string& ts, int idx) : tilesetName(ts), tileIndex(idx) {}

    bool IsEmpty() const { return tileIndex < 0; }

    bool operator==(const Tile& o) const
    {
        return tilesetName == o.tilesetName
            && tileIndex == o.tileIndex
            && flipX == o.flipX
            && flipY == o.flipY
            && collision == o.collision
            && properties == o.properties;
    }
};

} // namespace Editor::Map

#endif // _EDITOR_TILE_HPP__
