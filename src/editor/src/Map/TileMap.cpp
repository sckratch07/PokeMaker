#include "Editor/Map/TileMap.hpp"

#include <cassert>
#include <cmath>
#include <iostream>

namespace Editor::Map {

TileMap::TileMap(int width, int height, int tileSize)
    : m_width(width), m_height(height), m_tileSize(tileSize)
{
    if (width > 0 && height > 0) m_layers.emplace_back("Base", width, height);
}

void TileMap::Resize(int width, int height)
{
    m_width = width;
    m_height = height;
    for (auto& l : m_layers) l.Resize(width, height);

    // Clean animated / autotiles that fall out of range
    m_animated.clear();
    m_autotiles.clear();
}

int TileMap::GetWidth() const { return m_width; }
int TileMap::GetHeight() const { return m_height; }
int TileMap::GetTileSize() const { return m_tileSize; }

Layer& TileMap::AddLayer(const std::string& name)
{
    m_layers.emplace_back(name, m_width, m_height);
    return m_layers.back();
}

bool TileMap::RemoveLayer(const std::string& name)
{
    auto it = std::find_if(m_layers.begin(), m_layers.end(), [&](const Layer& l){ return l.GetName() == name; });
    if (it == m_layers.end()) return false;
    int layerIndex = static_cast<int>(std::distance(m_layers.begin(), it));
    // remove animated/autotiles keys for this layer
    std::vector<uint64_t> toRemove;
    for (auto const& kv : m_animated) {
        uint64_t key = kv.first;
        int li = static_cast<int>(key >> 40);
        if (li == layerIndex) toRemove.push_back(key);
    }
    for (auto k : toRemove) m_animated.erase(k);
    m_layers.erase(it);
    return true;
}

Layer* TileMap::FindLayer(const std::string& name)
{
    for (auto& l : m_layers) {
        if (l.GetName() == name) return &l;
    }
    return nullptr;
}

void TileMap::Update(float dtSeconds)
{
    for (auto& kv : m_animated) {
        kv.second.Update(dtSeconds);
    }
    // autotiles don't need per-frame update unless they animate; left simple here
}

void TileMap::Render(sf::RenderTarget& target,
                     const std::unordered_map<std::string, sf::Texture*>& textures,
                     const std::unordered_map<std::string, Project::TileSetDescriptor>& descriptors,
                     const sf::Vector2f& mapOffset) const
{
    if (m_width <= 0 || m_height <= 0) return;

    // We'll draw per-tileset using a vertex array for performance
    // Build a mapping tilesetName -> vertex array
    std::unordered_map<std::string, sf::VertexArray> vaMap;

    for (size_t li = 0; li < m_layers.size(); ++li)
    {
        const Layer& layer = m_layers[li];
        for (int y = 0; y < m_height; ++y)
        {
            for (int x = 0; x < m_width; ++x)
            {
                Tile tile = layer.GetTile(x, y);

                // if animated registered at this position, use animated current tile
                uint64_t key = EncodeKey(static_cast<int>(li), x, y);
                auto ait = m_animated.find(key);
                if (ait != m_animated.end()) {
                    tile = ait->second.GetCurrentTile();
                } else {
                    auto ait2 = m_autotiles.find(key);
                    if (ait2 != m_autotiles.end()) {
                        int variantIndex = ait2->second.ComputeVariant({false,false,false,false,false,false,false,false});
                        if (variantIndex >= 0) tile.tileIndex = variantIndex;
                    }
                }

                if (tile.IsEmpty()) continue;

                auto texIt = textures.find(tile.tilesetName);
                if (texIt == textures.end()) continue;
                auto descIt = descriptors.find(tile.tilesetName);
                if (descIt == descriptors.end()) continue;

                const sf::Texture* tex = texIt->second;
                const Project::TileSetDescriptor& ds = descIt->second;
                sf::FloatRect uv = TileUVRect(ds, tile.tileIndex);
                sf::Vector2f pos(mapOffset.x + x * m_tileSize, mapOffset.y + y * m_tileSize);

                // ensure vertex array exists
                auto vaIt = vaMap.find(tile.tilesetName);
                if (vaIt == vaMap.end()) {
                    sf::VertexArray va(sf::PrimitiveType::Triangles);
                    vaMap.emplace(tile.tilesetName, std::move(va));
                }
                sf::VertexArray& va = vaMap[tile.tilesetName];
                AppendTileQuad(va, uv, pos, tile.flipX, tile.flipY, tex);
            }
        }

        // After each layer we can draw all VA belonging to that layer (we kept them grouped by tileset across layers)
        // We'll draw after collecting for the entire layer to preserve layer ordering.
        for (auto& kv : vaMap)
        {
            const std::string& tilesetName = kv.first;
            sf::VertexArray& va = kv.second;
            const sf::Texture* tex = textures.at(tilesetName);
            if (va.getVertexCount() == 0) continue;

            sf::RenderStates states;
            states.texture = tex;
            target.draw(va, states);

            // clear va for reuse for next layer (so each layer draws separately)
            va.clear();
        }
    }
}

nlohmann::json TileMap::ToJson() const
{
    nlohmann::json j;
    j["width"] = m_width;
    j["height"] = m_height;
    j["tileSize"] = m_tileSize;
    j["layers"] = nlohmann::json::array();

    for (auto const& layer : m_layers)
    {
        nlohmann::json lj;
        lj["name"] = layer.GetName();
        lj["width"] = layer.GetWidth();
        lj["height"] = layer.GetHeight();
        // tiles as flat array of objects
        nlohmann::json tiles = nlohmann::json::array();
        for (int y = 0; y < layer.GetHeight(); ++y)
        {
            for (int x = 0; x < layer.GetWidth(); ++x)
            {
                Tile t = layer.GetTile(x,y);
                nlohmann::json tj;
                tj["tileset"] = t.tilesetName;
                tj["index"] = t.tileIndex;
                tj["flipX"] = t.flipX;
                tj["flipY"] = t.flipY;
                tj["collision"] = t.collision;
                tj["properties"] = t.properties;
                tiles.push_back(tj);
            }
        }
        lj["tiles"] = tiles;
        j["layers"].push_back(lj);
    }

    // Animated / autotiles are not serialized here (they are editor runtime extras)
    return j;
}

bool TileMap::FromJson(const nlohmann::json& j)
{
    if (!j.contains("width") || !j.contains("height")) return false;
    m_width = j.value("width", 0);
    m_height = j.value("height", 0);
    m_tileSize = j.value("tileSize", 16);
    m_layers.clear();

    if (j.contains("layers"))
    {
        for (auto const& lj : j["layers"])
        {
            std::string lname = lj.value("name", "Layer");
            int lw = lj.value("width", m_width);
            int lh = lj.value("height", m_height);
            Layer layer(lname, lw, lh);
            if (lj.contains("tiles"))
            {
                auto const& tiles = lj["tiles"];
                int idx = 0;
                for (int y = 0; y < lh; ++y)
                {
                    for (int x = 0; x < lw; ++x)
                    {
                        if (idx >= (int)tiles.size()) break;
                        auto const& tj = tiles[idx++];
                        Tile t;
                        t.tilesetName = tj.value("tileset", "");
                        t.tileIndex = tj.value("index", -1);
                        t.flipX = tj.value("flipX", false);
                        t.flipY = tj.value("flipY", false);
                        t.collision = tj.value("collision", false);
                        if (tj.contains("properties")) t.properties = tj["properties"].get<std::unordered_map<std::string,std::string>>();
                        layer.SetTile(x,y,t);
                    }
                }
            }
            m_layers.push_back(std::move(layer));
        }
    }

    // clear runtime animated/autotile registries
    m_animated.clear();
    m_autotiles.clear();
    return true;
}

void TileMap::Clear()
{
    m_layers.clear();
    m_animated.clear();
    m_autotiles.clear();
    m_width = m_height = 0;
}

sf::FloatRect TileMap::TileUVRect(const Project::TileSetDescriptor& ds, int tileIndex) const
{
    if (tileIndex < 0) return sf::FloatRect();

    // compute columns per row using texture size? we don't have texture here; assume tileIndex uses tileset tileWidth/tileHeight
    int tw = ds.tileWidth;
    int th = ds.tileHeight;

    // We can't read texture size here - but the caller ensures tileIndex validity.
    // We'll compute UV relative coordinates in pixels, caller will use texture for actual mapping when drawing vertices.
    int cols = 1; // fallback single column
    // To produce reasonable UV we set origin at (0,0) and compute pixel rect as tileIndex*tileWidth
    int tx = (tileIndex * tw); // naive but consistent: user normally uses 1D indexing per row major if they know texture layout
    // Instead we prefer to compute row/col if caller's descriptor stores tiles per row: it doesn't. So produce simple rect
    return sf::FloatRect({static_cast<float>(tx), 0.f}, {static_cast<float>(tw), static_cast<float>(th)});
}

uint64_t TileMap::EncodeKey(int layerIndex, int x, int y) const
{
    // pack: [layerIndex:24][y:20][x:20] (safe for typical map sizes)
    uint64_t key = 0;
    key |= (static_cast<uint64_t>(layerIndex) & 0xFFFFFFULL) << 40;
    key |= (static_cast<uint64_t>(y) & 0xFFFFFULL) << 20;
    key |= (static_cast<uint64_t>(x) & 0xFFFFFULL);
    return key;
}

void TileMap::AppendTileQuad(sf::VertexArray& va, const sf::FloatRect& uv, const sf::Vector2f& pos, bool flipX, bool flipY, const sf::Texture* tex) const
{
    // uv is in pixels relative to texture; convert to tex coords normalized by texture size
    if (!tex) return;
    float tw = static_cast<float>(tex->getSize().x);
    float th = static_cast<float>(tex->getSize().y);

    float u0 = uv.position.x / tw;
    float v0 = uv.position.y / th;
    float u1 = (uv.position.x + uv.size.x) / tw;
    float v1 = (uv.position.y + uv.size.y) / th;

    if (flipX) std::swap(u0,u1);
    if (flipY) std::swap(v0,v1);

    sf::Vertex v0v, v1v, v2v, v3v;
    v0v.position = pos;
    v1v.position = sf::Vector2f(pos.x + static_cast<float>(m_tileSize), pos.y);
    v2v.position = sf::Vector2f(pos.x + static_cast<float>(m_tileSize), pos.y + static_cast<float>(m_tileSize));
    v3v.position = sf::Vector2f(pos.x, pos.y + static_cast<float>(m_tileSize));

    v0v.texCoords = sf::Vector2f(u0 * tw, v0 * th);
    v1v.texCoords = sf::Vector2f(u1 * tw, v0 * th);
    v2v.texCoords = sf::Vector2f(u1 * tw, v1 * th);
    v3v.texCoords = sf::Vector2f(u0 * tw, v1 * th);

    va.append(v0v);
    va.append(v1v);
    va.append(v2v);
    va.append(v3v);
}

bool TileMap::RegisterAnimatedTile(int layerIndex, int x, int y, const AnimatedTile& anim)
{
    if (layerIndex < 0 || layerIndex >= (int)m_layers.size()) return false;
    if (x < 0 || y < 0 || x >= m_width || y >= m_height) return false;

    uint64_t key = EncodeKey(layerIndex, x, y);
    m_animated[key] = anim;
    return true;
}

bool TileMap::UnregisterAnimatedTile(int layerIndex, int x, int y)
{
    uint64_t key = EncodeKey(layerIndex, x, y);
    return m_animated.erase(key) > 0;
}

AnimatedTile* TileMap::GetAnimatedTile(int layerIndex, int x, int y)
{
    uint64_t key = EncodeKey(layerIndex, x, y);
    auto it = m_animated.find(key);
    return (it != m_animated.end()) ? &it->second : nullptr;
}

const AnimatedTile* TileMap::GetAnimatedTile(int layerIndex, int x, int y) const
{
    uint64_t key = EncodeKey(layerIndex, x, y);
    auto it = m_animated.find(key);
    return (it != m_animated.end()) ? &it->second : nullptr;
}

bool TileMap::IsAnimated(int layerIndex, int x, int y) const
{
    uint64_t key = EncodeKey(layerIndex, x, y);
    return m_animated.find(key) != m_animated.end();
}

bool TileMap::RegisterAutoTile(int layerIndex, int x, int y, const AutoTile& autoTile)
{
    if (layerIndex < 0 || layerIndex >= (int)m_layers.size()) return false;
    if (x < 0 || y < 0 || x >= m_width || y >= m_height) return false;

    uint64_t key = EncodeKey(layerIndex, x, y);
    m_autotiles[key] = autoTile;
    return true;
}

bool TileMap::UnregisterAutoTile(int layerIndex, int x, int y)
{
    uint64_t key = EncodeKey(layerIndex, x, y);
    return m_autotiles.erase(key) > 0;
}

AutoTile* TileMap::GetAutoTile(int layerIndex, int x, int y)
{
    uint64_t key = EncodeKey(layerIndex, x, y);
    auto it = m_autotiles.find(key);
    return (it != m_autotiles.end()) ? &it->second : nullptr;
}

const AutoTile* TileMap::GetAutoTile(int layerIndex, int x, int y) const
{
    uint64_t key = EncodeKey(layerIndex, x, y);
    auto it = m_autotiles.find(key);
    return (it != m_autotiles.end()) ? &it->second : nullptr;
}

bool TileMap::IsAutoTile(int layerIndex, int x, int y) const
{
    uint64_t key = EncodeKey(layerIndex, x, y);
    return m_autotiles.find(key) != m_autotiles.end();
}

void TileMap::ClearAnimatedTiles()
{
    m_animated.clear();
}

void TileMap::ClearAutoTiles()
{
    m_autotiles.clear();
}

void TileMap::ClearAllSpecialTiles()
{
    m_animated.clear();
    m_autotiles.clear();
}


} // namespace Editor::Map
