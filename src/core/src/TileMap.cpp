#include "Core/TileMap.hpp"
#include <stdexcept>

namespace Core
{
TileMap TileMap::MakeEmpty(const std::string& id, int width, int height)
{
    TileMap m;
    m.id = id;
    m.width = width;
    m.height = height;
    Layer base;
    base.name = "base";
    base.type = LayerType::TileLayer;
    base.tiles.resize(static_cast<size_t>(width) * static_cast<size_t>(height));
    m.layers.push_back(std::move(base));
    return m;
}

bool TileMap::Validate() const noexcept
{
    if (width <= 0 || height <= 0) return false;
    const size_t expected = static_cast<size_t>(width) * static_cast<size_t>(height);
    for (const auto &l : layers)
    {
        if (l.type == LayerType::TileLayer)
        {
            if (l.tiles.size() != expected) return false;
        }
    }
    return true;
}

Layer* TileMap::GetLayerByName(const std::string& name)
{
    for (auto &l : layers)
    {
        if (l.name == name) return &l;
    }
    return nullptr;
}

const Layer* TileMap::GetLayerByNameConst(const std::string& name) const
{
    for (const auto &l : layers)
    {
        if (l.name == name) return &l;
    }
    return nullptr;
}

void to_json(nlohmann::json& j, const TileMap& m)
{
    j = nlohmann::json::object();
    j["id"] = m.id;
    j["width"] = m.width;
    j["height"] = m.height;
    j["tilesets"] = nlohmann::json::array();
    for (const auto &ts : m.tilesets) j["tilesets"].push_back(ts);
    j["layers"] = nlohmann::json::array();
    for (const auto &l : m.layers) j["layers"].push_back(l);
    if (!m.properties.empty()) j["properties"] = m.properties;
}

void from_json(const nlohmann::json& j, TileMap& m)
{
    m.id = j.value("id", std::string());
    m.width = j.value("width", 0);
    m.height = j.value("height", 0);
    m.tilesets.clear();
    if (j.contains("tilesets") && j["tilesets"].is_array())
    {
        for (const auto &elem : j["tilesets"])
        {
            TileSet ts;
            from_json(elem, ts);
            m.tilesets.push_back(std::move(ts));
        }
    }
    m.layers.clear();
    if (j.contains("layers") && j["layers"].is_array())
    {
        for (const auto &elem : j["layers"])
        {
            Layer l;
            from_json(elem, l);
            m.layers.push_back(std::move(l));
        }
    }
    if (j.contains("properties") && j["properties"].is_object())
    {
        m.properties = j["properties"].get<std::map<std::string, nlohmann::json>>();
    }
    else
    {
        m.properties.clear();
    }
}

} // namespace core
