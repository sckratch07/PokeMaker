#include "Renderer/MapRenderer.hpp"
#include <stdexcept>

namespace Renderer
{
MapRenderer::MapRenderer() = default;

void MapRenderer::SetTileMap(const Core::TileMap& map) {
    m_tileMap = &map;
    m_tileDrawData.clear();

    // Préparer les sprites pour chaque tile animée
    for (const auto& layer : map.layers)
    {
        if (layer.type != Core::LayerType::TileLayer) continue;
        for (const auto& tile : layer.tiles)
        {
            if (tile.IsAnimated())
            {
                TileDrawData data =
                {
                    CreateTileSprite(tile), 0, 0.0f
                };
                m_tileDrawData[&tile] = data;
            }
        }
    }
}

void MapRenderer::SetTextureManager(Core::ResourceManager<sf::Texture>* manager)
{
    m_textureManager = manager;
}

sf::Texture* MapRenderer::GetTextureForTileset(const std::string& tilesetId) const
{
    if (!m_textureManager) return nullptr;
    return m_textureManager->Get(tilesetId).get();
}

sf::Sprite MapRenderer::CreateTileSprite(const Core::Tile& tile) const
{
    sf::Texture* tex = GetTextureForTileset(tile.tileset_id);
    if (!tex)
    {
        sf::Texture nullText;
        return sf::Sprite(nullText);
    }

    sf::Sprite sprite(*tex);

    int tileWidth = 32;
    int tileHeight = 32;

    // Chercher la taille depuis le tileset
    if (m_tileMap) {
        for (const auto& ts : m_tileMap->tilesets) {
            if (ts.id == tile.tileset_id) {
                tileWidth = ts.tile_width;
                tileHeight = ts.tile_height;
                break;
            }
        }
    }

    int col = 0;
    if (!tile.IsAnimated() && tile.tile_index >= 0) col = tile.tile_index;

    int tx = (col % (tex->getSize().x / tileWidth)) * tileWidth;
    int ty = (col / (tex->getSize().x / tileWidth)) * tileHeight;

    sprite.setTexture(*tex);
    sprite.setTextureRect(sf::IntRect(tx, ty, tileWidth, tileHeight));

    return sprite;
}

void MapRenderer::UpdateTileAnimation(const Core::Tile& tile, TileDrawData& data, float deltaTime) {
    if (!tile.IsAnimated() || tile.frames.empty()) return;

    data.frameTimer += deltaTime * 1000.0f; // convertir en ms
    const auto& frame = tile.frames[data.currentFrame];

    if (data.frameTimer >= frame.duration_ms) {
        data.frameTimer -= frame.duration_ms;
        data.currentFrame++;
        if (data.currentFrame >= tile.frames.size()) {
            data.currentFrame = tile.loop ? 0 : tile.frames.size() - 1;
        }

        sf::Texture* tex = GetTextureForTileset(tile.frames[data.currentFrame].tileset_id);
        if (tex) {
            int tileWidth = 32, tileHeight = 32;
            if (m_tileMap) {
                for (const auto& ts : m_tileMap->tilesets) {
                    if (ts.id == tile.frames[data.currentFrame].tileset_id) {
                        tileWidth = ts.tile_width;
                        tileHeight = ts.tile_height;
                        break;
                    }
                }
            }
            int col = tile.frames[data.currentFrame].tile_index;
            int tx = (col % (tex->getSize().x / tileWidth)) * tileWidth;
            int ty = (col / (tex->getSize().x / tileWidth)) * tileHeight;
            data.sprite.setTexture(*tex);
            data.sprite.setTextureRect(sf::IntRect(tx, ty, tileWidth, tileHeight));
        }
    }
}

void MapRenderer::Update(float deltaTime) {
    if (!m_tileMap) return;
    for (auto& [tilePtr, data] : m_tileDrawData) {
        UpdateTileAnimation(*tilePtr, data, deltaTime);
    }
}

void MapRenderer::Render(sf::RenderTarget& target) {
    if (!m_tileMap) return;

    for (const auto& layer : m_tileMap->layers) {
        if (layer.type != core::LayerType::TileLayer) continue;

        int width = m_tileMap->width;
        int height = m_tileMap->height;

        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                const auto& tile = layer.GetTileAt(width, x, y);

                sf::Sprite sprite;

                auto it = m_tileDrawData.find(&tile);
                if (it != m_tileDrawData.end()) {
                    sprite = it->second.sprite;
                } else {
                    sprite = CreateTileSprite(tile);
                }

                sprite.setPosition(static_cast<float>(x * sprite.getTextureRect().width),
                                   static_cast<float>(y * sprite.getTextureRect().height));
                target.draw(sprite);
            }
        }
    }
}

} // namespace renderer
