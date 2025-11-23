#include "Renderer/TileRenderer.hpp"

namespace Renderer
{

    TileRenderer::TileRenderer(Renderer& renderer)
        : m_renderer(renderer), m_tileset(nullptr)
    {
    }

    void TileRenderer::setTileset(const sf::Texture& texture, int tileWidth, int tileHeight)
    {
        m_tileset = &texture;
        m_tileWidth = tileWidth;
        m_tileHeight = tileHeight;
    }

    void TileRenderer::drawTile(int tileIndex, float x, float y)
    {
        if (!m_tileset)
            return;

        int columns = m_tileset->getSize().x / m_tileWidth;
        int tx = tileIndex % columns;
        int ty = tileIndex / columns;

        sf::Sprite sprite(*m_tileset);
        sprite.setTextureRect(sf::IntRect(
            {tx * m_tileWidth, ty * m_tileHeight},
            {m_tileWidth, m_tileHeight}
        ));

        sprite.setPosition({x, y});

        m_renderer.draw(sprite);
    }

} // namespace Renderer
