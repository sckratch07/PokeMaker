#include "Tile.hpp"

Tile::Tile() : sprite({0, 0}), size(0, 0), position(0, 0), textureRect({0, 0}, {0, 0}), collidable(false), tilesetIndex(-1) {}

Tile::Tile(const sf::Vector2i& size, const sf::Vector2i& pos, const sf::Texture& texture, const sf::IntRect& rect, int tileset)
    : sprite(sf::Vector2f(size)), size(size), position(pos), textureRect(rect), collidable(false), tilesetIndex(tileset)
{
    sprite.setPosition({ (float)pos.x, (float)pos.y });
    collisionSprite = sprite;
    collisionSprite.setFillColor(sf::Color(0, 0, 0, 75));
    sprite.setTexture(&texture);
    sprite.setTextureRect(rect);
}

void Tile::Draw(sf::RenderWindow& window, bool& drawCollision)
{
    if (tilesetIndex < 0) return;
    window.draw(sprite);
    if (collidable && drawCollision) window.draw(collisionSprite);
}

json Tile::Serialize() const
{
    json j;
    j["size"] = { sprite.getSize().x, sprite.getSize().y},
    j["position"] = { position.x, position.y };
    j["textureRect"] = { textureRect.position.x, textureRect.position.y, textureRect.size.x, textureRect.size.y };
    j["collidable"] = collidable;
    j["tilesetIndex"] = tilesetIndex;
    return j;
}

void Tile::Deserialize(const json& jsonData, std::vector<Tileset*> tilesets)
{
    if (jsonData.contains("position") && jsonData["position"].is_array())
    {
        position.x = jsonData["position"][0];
        position.y = jsonData["position"][1];
    }

    if (jsonData.contains("size") && jsonData["size"].is_array())
    {
        size.x = jsonData["size"][0];
        size.y = jsonData["size"][1];
    }

    if (jsonData.contains("textureRect") && jsonData["textureRect"].is_array() && jsonData["textureRect"].size() == 4)
    {
        textureRect.position.x = jsonData["textureRect"][0];
        textureRect.position.y = jsonData["textureRect"][1];
        textureRect.size.x = jsonData["textureRect"][2];
        textureRect.size.y = jsonData["textureRect"][3];
    }

    collidable = jsonData["collidable"];
    tilesetIndex = jsonData["tilesetIndex"];

    if (tilesetIndex >= 0)
    {
        sprite.setSize(sf::Vector2f(size));
        sprite.setPosition({ (float)position.x, (float)position.y });
        collisionSprite = sprite;
        collisionSprite.setFillColor(sf::Color(0, 0, 0, 75));
        sprite.setTextureRect(textureRect);
        sprite.setTexture(&tilesets[tilesetIndex]->GetTexture());
    }
}

void Tile::SetTransparency(uint8_t alpha)
{
    sf::Color tileColor = sprite.getFillColor();
    tileColor.a = alpha;
    sprite.setFillColor(tileColor);
}
