#pragma once
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Tile.hpp"
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class Layer {
public:
    Layer();
    Layer(const std::string& name, int id, sf::Vector2i& size);

    void SetTile(int x, int y, const Tile& tile);
    Tile* GetTile(int x, int y);
    std::vector<std::vector<Tile>> GetTiles();
    void Render(sf::RenderWindow& window);
    void Clear();

    json Serialize() const;
    void Deserialize(const json& jsonData);

    // Accesseurs
    const std::string& GetName() const { return name; }
    int GetID() const { return id; }
    bool IsVisible() const { return visible; }
    void SetVisible(bool v) { visible = v; }

private:
    std::string name;
    int id;
    bool visible;
    float opacity;
    std::vector<std::vector<Tile>> tiles;
};
