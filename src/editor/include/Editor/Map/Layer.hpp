#ifndef _EDITOR_LAYER_HPP__
#define _EDITOR_LAYER_HPP__

/**
 * @file Layer.hpp
 * @brief Représentation d'une couche (layer) contenant des Tiles.
 *
 * Chaque Layer contient un tableau 2D (width x height) de Tile.
 */

#include <string>
#include <vector>
#include <cstddef>
#include "Editor/Map/Tile.hpp"

namespace Editor::Map {

/**
 * @class Layer
 * @brief Conteneur de tiles 2D, méthodes utilitaires pour accès/édition.
 */
class Layer
{
public:
    Layer() = default;
    Layer(const std::string& name, int width, int height);

    void Resize(int width, int height);

    int GetWidth() const { return m_width; }
    int GetHeight() const { return m_height; }
    const std::string& GetName() const { return m_name; }
    void SetName(const std::string& name) { m_name = name; }

    /// Accès direct (const / non-const). Si coord hors-bounds retourne une tile vide (const) ou ignore (non-const).
    Tile GetTile(int x, int y) const;
    Tile& At(int x, int y); // may throw std::out_of_range if invalid
    void SetTile(int x, int y, const Tile& tile);

    /// Clears layer (set all tiles to empty)
    void Clear();

    /// Fill area rectangle with tile (x,y inclusive start, width,height)
    void FillRect(int startX, int startY, int w, int h, const Tile& tile);

private:
    std::string m_name = "Layer";
    int m_width = 0;
    int m_height = 0;
    std::vector<Tile> m_tiles; // row-major: y * width + x

    inline bool inBounds(int x, int y) const { return x >= 0 && y >= 0 && x < m_width && y < m_height; }
};

} // namespace Editor::Map

#endif // _EDITOR_LAYER_HPP__
