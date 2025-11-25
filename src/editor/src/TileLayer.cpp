#include "Editor/TileLayer.hpp"

namespace Editor {

TileLayer::TileLayer()
    : name("Layer"),
      type(LayerType::Ground),
      size({16, 16})
{
    tiles.resize(size.x * size.y);
}

TileLayer::TileLayer(const std::string& n, LayerType t, sf::Vector2u s)
    : name(n),
      type(t),
      size(s)
{
    tiles.resize(size.x * size.y);
}

Tile* TileLayer::GetTile(unsigned x, unsigned y)
{
    if (x >= size.x || y >= size.y)
        return nullptr;
    return &tiles[Index(x, y)];
}

const Tile* TileLayer::GetTile(unsigned x, unsigned y) const
{
    if (x >= size.x || y >= size.y)
        return nullptr;
    return &tiles[Index(x, y)];
}

void TileLayer::SetTile(unsigned x, unsigned y, const Tile& tile)
{
    if (x >= size.x || y >= size.y)
        return;
    tiles[Index(x, y)] = tile;
}

void TileLayer::Resize(sf::Vector2u newSize)
{
    size = newSize;
    tiles.clear();
    tiles.resize(size.x * size.y);
}

void TileLayer::Clear()
{
    for (auto& t : tiles)
        t = Tile(); // tile par défaut
}

} // namespace Editor
