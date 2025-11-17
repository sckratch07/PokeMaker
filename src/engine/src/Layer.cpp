#include <Layer.hpp>
#include <Logger.hpp>

namespace Engine
{
    Layer::Layer(int width, int height, LayerType type)
        : m_width(width), m_height(height), m_type(type)
    {
        m_tiles.resize(width * height, -1);
        m_frameTimers.resize(width * height, 0.f);
    }

    void Layer::setTile(int x, int y, int tileId)
    {
        if (x < 0 || x >= m_width || y < 0 || y >= m_height) return;
        m_tiles[y * m_width + x] = tileId;
        m_frameTimers[y * m_width + x] = 0.f;
    }

    int Layer::getTile(int x, int y) const
    {
        if (x < 0 || x >= m_width || y < 0 || y >= m_height) return -1;
        return m_tiles[y * m_width + x];
    }

    void Layer::setTileset(std::shared_ptr<Tileset> tileset)
    {
        m_tileset = tileset;
    }

    void Layer::update(float dt)
    {
        if (!m_tileset) return;

        for (int i = 0; i < static_cast<int>(m_tiles.size()); ++i)
        {
            int tileId = m_tiles[i];
            if (tileId < 0 || tileId >= m_tileset->getTileCount()) continue;

            const Tile& tile = m_tileset->getTile(tileId);
            if (!tile.animated || tile.frames.empty()) continue;

           m_frameTimers[i] += dt;
            if (m_frameTimers[i] >= tile.frameTime)
            {
                m_frameTimers[i] = 0.f;
                // Animation: rotate frames
                // Pour l'instant, juste on met à jour l’ID pour la frame suivante
                int nextFrame = (tile.textureRect.position.x / tile.textureRect.size.x + 1) % tile.frames.size();
            }
        }
    }

    void Layer::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        if (!m_tileset) return;
        sf::Sprite sprite(m_tileset->getTexture());

        for (int y = 0; y < m_height; ++y)
        {
            for (int x = 0; x < m_width; ++x)
            {
                int tileId = getTile(x, y);
                if (tileId < 0) continue;

                const Tile& tile = m_tileset->getTile(tileId);
                sprite.setTextureRect(tile.textureRect);
                sprite.setPosition(sf::Vector2f(x * tile.textureRect.size.x, y * tile.textureRect.size.y));
                target.draw(sprite, states);
            }
        }
    }

} // namespace Engine
