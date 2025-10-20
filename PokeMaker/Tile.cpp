#include "Tile.hpp"

Tile::Tile() : sprite({32, 32}), position(0, 0), textureRect({0, 0}, {32, 32}), collidable(false), layerIndex(0), tilesetIndex(0) {}

Tile::Tile(const sf::Vector2i& pos, const sf::Texture& texture, const sf::IntRect& rect, int layer, int tileset) : sprite(sf::Vector2f(rect.size)), position(pos), textureRect(rect), collidable(false), layerIndex(layer), tilesetIndex(tileset)
{
    sprite.setPosition({ (float)pos.x, (float)pos.y });
    sprite.setTexture(&texture);
    sprite.setTextureRect(rect);
}

void Tile::Draw(sf::RenderWindow& window)
{
    window.draw(sprite);
}

void Tile::SetTransparency(uint8_t alpha)
{
    sf::Color c = sprite.getFillColor();
    c.a = alpha;
    sprite.setFillColor(c);
}

json Tile::Serialize() const
{
    json j;
    j["position"] = { position.x, position.y };
    j["textureRect"] = { textureRect.position.x, textureRect.position.y, textureRect.size.x, textureRect.size.y };
    j["collidable"] = collidable;
    j["layerIndex"] = layerIndex;
    return j;
}

void Tile::Deserialize(const json& jsonData)
{
    if (jsonData.contains("position") && jsonData["position"].is_array()) {
        position.x = jsonData["position"][0];
        position.y = jsonData["position"][1];
    }
    if (jsonData.contains("textureRect") && jsonData["textureRect"].is_array() && jsonData["textureRect"].size() == 4) {
        textureRect.position.x = jsonData["textureRect"][0];
        textureRect.position.y = jsonData["textureRect"][1];
        textureRect.size.x = jsonData["textureRect"][2];
        textureRect.size.y = jsonData["textureRect"][3];
    }
    collidable = jsonData.value("collidable", false);
    layerIndex = jsonData.value("layerIndex", 0);

    sprite.setSize(sf::Vector2f(textureRect.size));
    sprite.setPosition({ (float)position.x, (float)position.y });
    sprite.setTextureRect(textureRect);
}
