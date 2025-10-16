#include "Map.hpp"

Map::Map() : name(""), size(0, 0), tileSize(32, 32), tileset(nullptr) {}

Map::Map(const std::string& name, const sf::Vector2i& size, const sf::Vector2i& tileSize) : name(name), size(size), tileSize(tileSize), tileset(nullptr) {}

void Map::AddLayer(const std::string& layerName)
{
    int id = static_cast<int>(layers.size());
    layers.emplace_back(layerName, id, GetSize());
}

void Map::Render(sf::RenderWindow& window)
{
    for (auto& layer : layers) {
        layer.Render(window);
    }
}

json Map::Serialize() const
{
    json j;
    j["name"] = name;
    j["size"] = { size.x, size.y };
    j["tileSize"] = { tileSize.x, tileSize.y };

    j["layers"] = json::array();
    for (const auto& layer : layers) {
        j["layers"].push_back(layer.Serialize());
    }

    if (tileset)
        j["tileset"] = tileset->Serialize();
    else
        j["tileset"] = nullptr;

    return j;
}

void Map::Deserialize(const json& jsonData)
{
    name = jsonData.value("name", "");
    if (jsonData.contains("size") && jsonData["size"].is_array() && jsonData["size"].size() == 2) {
        size.x = jsonData["size"][0];
        size.y = jsonData["size"][1];
    }

    if (jsonData.contains("tileSize") && jsonData["tileSize"].is_array() && jsonData["tileSize"].size() == 2) {
        tileSize.x = jsonData["tileSize"][0];
        tileSize.y = jsonData["tileSize"][1];
    }

    layers.clear();
    if (jsonData.contains("layers") && jsonData["layers"].is_array()) {
        for (const auto& layerJson : jsonData["layers"]) {
            Layer layer;
            layer.Deserialize(layerJson);
            layers.push_back(layer);
        }
    }

    if (jsonData.contains("tileset") && !jsonData["tileset"].is_null()) {
        tileset = new Tileset();
        tileset->Deserialize(jsonData["tileset"]);
    }
    else {
        tileset = nullptr;
    }
}
