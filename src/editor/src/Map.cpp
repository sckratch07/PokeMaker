#include "Editor/Map.hpp"

namespace Editor {

Map::Map() 
    : width(0), height(0)
{
}

Map::Map(const std::string& name, int width, int height)
    : name(name), width(width), height(height)
{
}

nlohmann::json Map::toJson() const
{
    nlohmann::json j;
    j["name"] = name;
    j["width"] = width;
    j["height"] = height;

    // Layers
    j["layers"] = nlohmann::json::array();
    for (const auto& layer : layers)
    {
        nlohmann::json jl;
        jl["name"] = layer.name;
        jl["visible"] = layer.visible;
        jl["locked"] = layer.locked;
        jl["data"] = layer.data;
        j["layers"].push_back(jl);
    }

    // Links
    j["links"] = nlohmann::json::array();
    for (const auto& link : links)
        j["links"].push_back(link.toJson());

    return j;
}

void Map::fromJson(const nlohmann::json& j)
{
    name = j.at("name").get<std::string>();
    width = j.at("width").get<int>();
    height = j.at("height").get<int>();

    layers.clear();
    for (auto& jl : j.at("layers"))
    {
        Layer layer;
        layer.name = jl["name"];
        layer.visible = jl["visible"];
        layer.locked = jl["locked"];
        layer.data = jl["data"].get<std::vector<int>>();
        layers.push_back(layer);
    }

    links.clear();
    for (auto& jl : j.at("links"))
    {
        MapLink link;
        link.fromJson(jl);
        links.push_back(link);
    }
}

} // namespace Editor
