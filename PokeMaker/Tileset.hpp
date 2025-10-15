#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class Tileset {
public:
    Tileset();

    bool LoadFromFile(const std::string& path);
    sf::IntRect GetTileTextureRect(int id) const;

    json Serialize() const;
    void Deserialize(const json& jsonData);

    // Accesseurs
    const std::string& GetName() const { return name; }
    const sf::Texture& GetTexture() const { return texture; }
    const sf::Vector2i& GetTileSize() const { return tileSize; }

private:
    std::string name;
    sf::Texture texture;
    sf::Vector2i tileSize = { 0,0 };
    int columns;
    int rows;
};
