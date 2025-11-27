#include "Core/Layer.hpp"
#include <stdexcept>

namespace Core
{
const Tile& Layer::GetTileAt(int width, int x, int y) const
{
    if (width <= 0) throw std::out_of_range("Layer::GetTileAt: width must be > 0");
    if (x < 0 || y < 0) throw std::out_of_range("Layer::GetTileAt: negative coordinates");
    int idx = y * width + x;
    if (idx < 0 || idx >= static_cast<int>(tiles.size())) throw std::out_of_range("Layer::GetTileAt: index out of bounds");
    return tiles[idx];
}

Tile& Layer::GetTileAt(int width, int x, int y)
{
    if (width <= 0) throw std::out_of_range("Layer::GetTileAt: width must be > 0");
    if (x < 0 || y < 0) throw std::out_of_range("Layer::GetTileAt: negative coordinates");
    int idx = y * width + x;
    if (idx < 0 || idx >= static_cast<int>(tiles.size())) throw std::out_of_range("Layer::GetTileAt: index out of bounds");
    return tiles[idx];
}

void to_json(nlohmann::json& j, const Layer& l)
{
    j = nlohmann::json::object();
    j["name"] = l.name;
    j["type"] = static_cast<int>(l.type);
    j["properties"] = l.properties;
    j["tiles"] = nlohmann::json::array();
    for (const auto &t : l.tiles) j["tiles"].push_back(t);
}

void from_json(const nlohmann::json& j, Layer& l)
{
    l.name = j.value("name", std::string());
    l.type = static_cast<LayerType>(j.value("type", static_cast<int>(LayerType::TileLayer)));
    if (j.contains("properties") && j["properties"].is_object())
    {
        l.properties = j["properties"].get<std::map<std::string, nlohmann::json>>();
    }
    else
    {
        l.properties.clear();
    }
    l.tiles.clear();
    if (j.contains("tiles") && j["tiles"].is_array())
    {
        for (const auto &elem : j["tiles"])
        {
            Tile t;
            from_json(elem, t);
            l.tiles.push_back(std::move(t));
        }
    }
}
} // namespace core
