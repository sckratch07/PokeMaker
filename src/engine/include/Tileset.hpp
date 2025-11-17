#ifndef _ENGINE_TILESET_HPP__
#define _ENGINE_TILESET_HPP__

#include <Tile.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <memory>

namespace Engine
{
    class Tileset
    {
    public:
        Tileset() = default;
        ~Tileset() = default;

        bool loadFromFile(const std::string& imagePath, int tileWidth, int tileHeight, int spacing = 0);
        const sf::Texture& getTexture() const;
        const Tile& getTile(int id) const;
        int getTileCount() const;

    private:
        sf::Texture m_texture;
        std::vector<Tile> m_tiles;
        int m_tileWidth = 0;
        int m_tileHeight = 0;
        int m_spacing = 0;
    };

} // namespace Engine

#endif
