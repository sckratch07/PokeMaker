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

void Map::Render(sf::RenderWindow& window, bool& collisionMode, int& selectedLayer)
{
    for (int i = 0; i < layers.size(); i++)
    {
        bool drawCollision = (collisionMode && selectedLayer == i);
        layers[i].Render(window, drawCollision);
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

    return j;
}

void Map::Deserialize(const json& jsonData, std::vector<Tileset*> tilesets)
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
            layer.Deserialize(layerJson, tilesets);
            layers.push_back(layer);
        }
    }
}
