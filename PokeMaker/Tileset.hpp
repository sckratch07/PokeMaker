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
    const std::string& GetPath() const { return path; }
    const sf::Texture& GetTexture() const { return texture; }
    const sf::Vector2i& GetTileSize() const { return tileSize; }

private:
    std::string path;
    sf::Texture texture;
    sf::Vector2i tileSize = { 0,0 };
    int columns;
    int rows;
};
