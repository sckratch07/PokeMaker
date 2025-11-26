#include "Editor/Map/Layer.hpp"
#include <stdexcept>
#include <algorithm>

namespace Editor::Map {

Layer::Layer(const std::string& name, int width, int height)
    : m_name(name), m_width(width), m_height(height), m_tiles(width * height)
{
}

void Layer::Resize(int width, int height)
{
    std::vector<Tile> newTiles(width * height);
    int copyW = std::min(width, m_width);
    int copyH = std::min(height, m_height);

    for (int y = 0; y < copyH; ++y)
    {
        for (int x = 0; x < copyW; ++x)
        {
            newTiles[y * width + x] = m_tiles[y * m_width + x];
        }
    }

    m_width = width;
    m_height = height;
    m_tiles.swap(newTiles);
}

Tile Layer::GetTile(int x, int y) const
{
    if (!inBounds(x,y)) return Tile();
    return m_tiles[y * m_width + x];
}

Tile& Layer::At(int x, int y)
{
    if (!inBounds(x,y)) throw std::out_of_range("Layer::At out of range");
    return m_tiles[y * m_width + x];
}

void Layer::SetTile(int x, int y, const Tile& tile)
{
    if (!inBounds(x,y)) return;
    m_tiles[y * m_width + x] = tile;
}

void Layer::Clear()
{
    std::fill(m_tiles.begin(), m_tiles.end(), Tile());
}

void Layer::FillRect(int startX, int startY, int w, int h, const Tile& tile)
{
    for (int yy = startY; yy < startY + h; ++yy)
        for (int xx = startX; xx < startX + w; ++xx)
            SetTile(xx, yy, tile);
}

} // namespace Editor::Map
