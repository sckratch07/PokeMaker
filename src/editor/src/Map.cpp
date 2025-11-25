#include "Editor/Map.hpp"

namespace Editor {

Map::Map()
    : name("UnnamedMap"),
      type(MapType::Outdoor),
      size({32, 32})
{
}

void Map::AddLayer(const TileLayer& layer)
{
    layers.push_back(layer);
}

void Map::RemoveLayer(size_t index)
{
    if (index < layers.size())
        layers.erase(layers.begin() + index);
}

TileLayer* Map::GetLayer(const std::string& name)
{
    for (auto& l : layers)
        if (l.name == name)
            return &l;
    return nullptr;
}

const TileLayer* Map::GetLayer(const std::string& name) const
{
    for (auto& l : layers)
        if (l.name == name)
            return &l;
    return nullptr;
}

TileSet* Map::GetTilesetByName(const std::string& name)
{
    for (auto& t : tilesets)
        if (t.name == name)
            return &t;
    return nullptr;
}

const TileSet* Map::GetTilesetByName(const std::string& name) const
{
    for (auto& t : tilesets)
        if (t.name == name)
            return &t;
    return nullptr;
}

void Map::Clear()
{
    layers.clear();
    tilesets.clear();
    npcs.clear();
    properties.clear();
}

bool Map::IsValid() const
{
    if (size.x == 0 || size.y == 0) return false;
    if (layers.empty()) return false;
    return true;
}

} // namespace Editor
