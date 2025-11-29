#include "Renderer/TileAtlas.hpp"
#include <algorithm>
#include <stdexcept>


namespace Renderer
{
TileAtlas::TileAtlas()
{
    // par défaut le ResourceManager est sans loader ; l'utilisateur du Renderer
    // doit configurer un loader adapté (lambda qui charge sf::Texture depuis un path).
}

void TileAtlas::RegisterTileSet(const Core::TileSet& tileset)
{
    m_tilesets.emplace(tileset.id, tileset);
}

bool TileAtlas::LoadTextureForTileset(const std::string& tilesetId) {
    auto it = m_tilesets.find(tilesetId);
    if (it == m_tilesets.end()) return false;
    const Core::TileSet& ts = it->second;
    // si la texture est déjà chargée, rien à faire
    if (m_textureManager.Get(ts.id)) return true;

    // loader par défaut : charge via sf::Texture depuis le path
    // si aucun loader défini, on enregistre un loader temporaire
    if (!m_textureManager.Get("__loader_present_check__")) {
    try {
    m_textureManager.SetLoader([&](const std::string& path) -> TileAtlas::TexturePtr
    {
        auto tex = std::make_shared<sf::Texture>();
        if (!tex->loadFromFile(path)) return nullptr;
        tex->setSmooth(false);
        return tex;
    });
    }
    catch (...)
    {
    // ignore : SetLoader ne lance pas normalement
    }
}


try {
auto tex = m_textureManager.Load(ts.id, ts.path);
return tex != nullptr;
} catch (...) {
return false;
}
}


TileAtlas::TexturePtr TileAtlas::GetTexture(const std::string& tilesetId) const noexcept {
return m_textureManager.Get(tilesetId);
}


std::optional<sf::IntRect> TileAtlas::GetTileRect(const std::string& tilesetId, int tileIndex) const noexcept {
auto it = m_tilesets.find(tilesetId);
if (it == m_tilesets.end()) return std::nullopt;
const core::TileSet& ts = it->second;
if (tileIndex < 0) return std::nullopt;
if (ts.tile_width <= 0 || ts.tile_height <= 0) return std::nullopt;
int cols = ts.columns;
if (cols <= 0) {
// si columns non renseignées, calcule approximativement en supposant texture chargée
auto tex = m_textureManager.Get(ts.id);
if (!tex) return std::nullopt;
cols = tex->getSize().x / ts.tile_width;
if (cols <= 0) return std::nullopt;
}
int tx = tileIndex % cols;
int ty = tileIndex / cols;
return sf::IntRect(tx * ts.tile_width, ty * ts.tile_height, ts.tile_width, ts.tile_height);
}


std::vector<std::string> TileAtlas::GetRegisteredIds() const {
std::vector<std::string> ids;
ids.reserve(m_tilesets.size());
for (const auto &p : m_tilesets) ids.push_back(p.first);
return ids;
}


} // namespace renderer