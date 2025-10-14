#pragma once
#include <SFML/Graphics.hpp>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class Tile {
public:
    Tile();
    Tile(const sf::Vector2i& position, const sf::IntRect& textureRect, int layerIndex = 0);

    void Draw(sf::RenderWindow& window);
    void SetTransparency(uint8_t alpha);

    json Serialize() const;
    void Deserialize(const json& jsonData);

    // Accesseurs
    const sf::Vector2i& GetPosition() const { return position; }
    const sf::Vector2i& GetSize() const { return textureRect.size; }
    void SetCollidable(bool coll) { collidable = coll; }
    bool IsCollidable() const { return collidable; }

private:
    sf::Vector2i position;       // Position en tiles
    sf::IntRect textureRect;     // Portion de texture à afficher
    sf::Sprite* sprite = nullptr;
    bool collidable;
    int layerIndex;
};
