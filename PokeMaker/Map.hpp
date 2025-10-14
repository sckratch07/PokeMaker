#pragma once
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include "Layer.hpp"
#include "Tileset.hpp"
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class Map {
public:
    Map();
    Map(const std::string& name, const sf::Vector2i& size, const sf::Vector2i& tileSize);

    void AddLayer(const std::string& name);
    Layer& GetLayer(int id);
    std::vector<Layer> GetLayers();
    void Render(sf::RenderWindow& window);

    json Serialize() const;
    void Deserialize(const json& jsonData);

    // Accesseurs
    const std::string& GetName() const { return name; }
    const sf::Vector2i& GetSize() const { return size; }
    const sf::Vector2i& GetTileSize() const { return tileSize; }

private:
    std::string name;
    sf::Vector2i size; // taille en tiles
    sf::Vector2i tileSize; // taille d’une tuile en pixels
    std::vector<Layer> layers;
    Tileset* tileset; // pointeur vers le tileset utilisé
};
