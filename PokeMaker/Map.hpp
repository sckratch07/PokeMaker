#pragma once
#include "Layer.hpp"
#include "Tileset.hpp"

class Map {
public:
    Map();
    Map(const std::string& name, const sf::Vector2i& size, const sf::Vector2i& tileSize);

    void AddLayer(const std::string& name);
    void Render(sf::RenderWindow& window);

    json Serialize() const;
    void Deserialize(const json& jsonData, std::vector<Tileset*> tilesets);

    // Accesseurs
    inline Layer& GetLayer(int id) { return layers.at(id); };
    inline std::vector<Layer>& GetLayers() { return layers; };
    inline std::string& GetName() { return name; }
    inline sf::Vector2i& GetSize() { return size; }
    inline sf::Vector2i& GetTileSize() { return tileSize; }

private:
    std::string name;
    sf::Vector2i size; // taille en tiles
    sf::Vector2i tileSize; // taille d’une tuile en pixels
    std::vector<Layer> layers;
};
