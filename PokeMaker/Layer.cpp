#include "Layer.hpp"

Layer::Layer() : name(""), id(0), visible(true), opacity(1.0f) {}

Layer::Layer(const std::string& name, int id, sf::Vector2i& size) : name(name), id(id), visible(true), opacity(1.0f)
{
    tiles.resize((size_t)size.y);
    for (int i = 0; i < size.y; i++)
    {
        tiles[i].resize((size_t)size.x);
    }
}

void Layer::SetTile(int x, int y, const Tile& tile)
{
    if (y >= 0 && y < tiles.size() && x >= 0 && x < tiles[y].size())
    {
        tiles[y][x] = tile;
    }
}

Tile* Layer::GetTile(int x, int y)
{
    if (y >= 0 && y < tiles.size() && x >= 0 && x < tiles[y].size())
    {
        return &tiles[y][x];
    }
    return nullptr;
}

std::vector<std::vector<Tile>> Layer::GetTiles()
{
    return tiles;
}

void Layer::Render(sf::RenderWindow& window)
{
    if (!visible) return;

    for (auto& row : tiles)
    {
        for (auto& tile : row)
        {
            tile.Draw(window);
        }
    }
}

void Layer::Clear()
{
    for (auto& row : tiles)
    {
        row.clear();
    }
}

json Layer::Serialize() const
{
    json j;
    j["name"] = name;
    j["id"] = id;
    j["visible"] = visible;
    j["opacity"] = opacity;

    j["tiles"] = json::array();
    for (const auto& row : tiles)
    {
        json rowJson = json::array();
        for (const auto& tile : row)
        {
            rowJson.push_back(tile.Serialize());
        }
        j["tiles"].push_back(rowJson);
    }

    return j;
}

void Layer::Deserialize(const json& jsonData)
{
    name = jsonData.value("name", "");
    id = jsonData.value("id", 0);
    visible = jsonData.value("visible", true);
    opacity = jsonData.value("opacity", 1.0f);

    tiles.clear();
    if (jsonData.contains("tiles") && jsonData["tiles"].is_array())
    {
        for (const auto& rowJson : jsonData["tiles"])
        {
            std::vector<Tile> row;
            for (const auto& tileJson : rowJson)
            {
                Tile tile;
                tile.Deserialize(tileJson);
                row.push_back(tile);
            }
            tiles.push_back(row);
        }
    }
}
