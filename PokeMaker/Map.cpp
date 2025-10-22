#include "Map.hpp"

Map::Map() : name(""), size(0, 0), tileSize(32, 32) {}

Map::Map(const std::string& name, const sf::Vector2i& size, const sf::Vector2i& tileSize) : name(name), size(size), tileSize(tileSize) {}

void Map::AddLayer(const std::string& layerName)
{
    int id = 0;
    for (Layer layer : layers)
    {
        if (id != layer.GetID())
            continue;
        id++;
    }
    layers.push_back(Layer(layerName, id, size));
}

void Map::AddTileset(Tileset* tileset)
{
    tilesets.push_back(tileset);
}

void Map::Render(sf::RenderWindow& window)
{
    for (auto& layer : layers)
    {
        layer.Render(window);
    }
}

json Map::Serialize() const
{
    json j;
    j["name"] = name;
    j["size"] = { size.x, size.y };
    j["tileSize"] = { tileSize.x, tileSize.y };

    j["tilesets"] = json::array();
    for (const auto& tileset : tilesets) {
        j["tilesets"].push_back(tileset->Serialize());
    }

    j["layers"] = json::array();
    for (const auto& layer : layers) {
        j["layers"].push_back(layer.Serialize());
    }

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

    for (Tileset* tileset : tilesets) { delete tileset; }
    tilesets.clear();
    if (jsonData.contains("tilesets") && jsonData["tilesets"].is_array()) {
        for (const auto& tilesetJson : jsonData["tilesets"]) {
            Tileset* tileset = new Tileset;
            tileset->Deserialize(tilesetJson);
            tilesets.push_back(tileset);
        }
    }

    layers.clear();
    if (jsonData.contains("layers") && jsonData["layers"].is_array()) {
        for (const auto& layerJson : jsonData["layers"]) {
            Layer layer;
            layer.Deserialize(layerJson, tilesets);
            layers.push_back(layer);
        }
    }
}
