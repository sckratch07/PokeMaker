#pragma once
#include "Tileset.hpp"

class Tile {
public:
    Tile();
    Tile(const sf::Vector2i& position, const sf::Texture& texture, const sf::IntRect& textureRect, int tilesetIndex = 0);

    void Draw(sf::RenderWindow& window, bool& drawCollision);

    json Serialize() const;
    void Deserialize(const json& jsonData, std::vector<Tileset*> tilesets);

    void SetTransparency(uint8_t alpha);

    // Accesseurs
    const sf::Vector2i& GetPosition() const { return position; }
    const sf::Vector2i& GetSize() const { return textureRect.size; }
    void SetTilesetId(int index) { tilesetIndex = index; }
    int& GetTilesetId() { return tilesetIndex; }
    void SetCollidable(bool coll) { collidable = coll; }
    bool IsCollidable() const { return collidable; }

private:
    sf::Vector2i position;       // Position en tiles
    sf::IntRect textureRect;     // Portion de texture à afficher
    sf::RectangleShape sprite;
    sf::RectangleShape collisionSprite;
    bool collidable;
    int tilesetIndex;
};
