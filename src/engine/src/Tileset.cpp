#include <Tileset.hpp>
#include <Logger.hpp>

namespace Engine
{
    bool Tileset::loadFromFile(const std::string& imagePath, int tileWidth, int tileHeight, int spacing)
    {
        m_tileWidth = tileWidth;
        m_tileHeight = tileHeight;
        m_spacing = spacing;

        if (!m_texture.loadFromFile(imagePath))
        {
            Core::log("Failed to load tileset texture: " + imagePath, Core::LogLevel::Error);
            return false;
        }

        int columns = m_texture.getSize().x / (tileWidth + spacing);
        int rows = m_texture.getSize().y / (tileHeight + spacing);

        m_tiles.clear();
        int id = 0;
        for (int y = 0; y < rows; ++y)
        {
            for (int x = 0; x < columns; ++x)
            {
                Tile tile;
                tile.id = id++;
                tile.textureRect = sf::IntRect(
                    {x * (tileWidth + spacing), y * (tileHeight + spacing)},
                    {tileWidth, tileHeight}
                );
                m_tiles.push_back(tile);
            }
        }

        Core::log("Tileset loaded: " + imagePath + " with " + std::to_string(m_tiles.size()) + " tiles.", Core::LogLevel::Info);
        return true;
    }

    const sf::Texture& Tileset::getTexture() const
    {
        return m_texture;
    }

    const Tile& Tileset::getTile(int id) const
    {
        if (id >= 0 && id < static_cast<int>(m_tiles.size()))
            return m_tiles[id];
        static Tile empty;
        return empty;
    }

    int Tileset::getTileCount() const
    {
        return static_cast<int>(m_tiles.size());
    }

} // namespace Engine
