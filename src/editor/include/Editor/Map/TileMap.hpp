#ifndef _EDITOR_TILEMAP_HPP__
#define _EDITOR_TILEMAP_HPP__

/**
 * @file TileMap.hpp
 * @brief Contient plusieurs layers et gère le rendu / (dé)sérialisation simple d'une map.
 */

#include <vector>
#include <string>
#include <unordered_map>
#include <memory>

#include <SFML/Graphics.hpp>
#include <nlohmann/json.hpp>

#include "Editor/Map/Layer.hpp"
#include "Editor/Map/AnimatedTile.hpp"
#include "Editor/Map/AutoTile.hpp"
#include "Editor/Project/Project.hpp"

namespace Editor::Map {

/**
 * @class TileMap
 * @brief Structure de map avec plusieurs layers, capable de rendre les tiles.
 *
 * Render nécessite :
 *  - textures : map tilesetName -> sf::Texture*
 *  - descriptors : map tilesetName -> TileSetDescriptor
 *
 * La TileMap sait aussi (dé)sérialiser sa grille basique (par layer).
 */
class TileMap
{
public:
    TileMap() = default;
    TileMap(int width, int height, int tileSize);

    void Resize(int width, int height);

    int GetWidth() const;
    int GetHeight() const;
    int GetTileSize() const;

    Layer& AddLayer(const std::string& name);
    bool RemoveLayer(const std::string& name);
    Layer* FindLayer(const std::string& name);

    const std::vector<Layer>& GetLayers() const { return m_layers; }

    /// Update animations inside the map (animated tiles)
    void Update(float dtSeconds);

    /**
     * Rendu : textures est une map tilesetName -> sf::Texture*
     * descriptors est une map tilesetName -> TileSetDescriptor
     */
    void Render(sf::RenderTarget& target,
                const std::unordered_map<std::string, sf::Texture*>& textures,
                const std::unordered_map<std::string, Project::TileSetDescriptor>& descriptors,
                const sf::Vector2f& mapOffset = sf::Vector2f(0.f,0.f)) const;

    // (dé)sérialisation JSON basique (structures de layers & tiles)
    nlohmann::json ToJson() const;
    bool FromJson(const nlohmann::json& j);

    // Accès / utilitaires
    void Clear();

    // -----------------------------
    // AnimatedTile utilities
    // -----------------------------
    bool RegisterAnimatedTile(int layerIndex, int x, int y, const AnimatedTile& anim);
    bool UnregisterAnimatedTile(int layerIndex, int x, int y);
    AnimatedTile* GetAnimatedTile(int layerIndex, int x, int y);
    const AnimatedTile* GetAnimatedTile(int layerIndex, int x, int y) const;
    bool IsAnimated(int layerIndex, int x, int y) const;

    // -----------------------------
    // AutoTile utilities
    // -----------------------------
    bool RegisterAutoTile(int layerIndex, int x, int y, const AutoTile& autoTile);
    bool UnregisterAutoTile(int layerIndex, int x, int y);
    AutoTile* GetAutoTile(int layerIndex, int x, int y);
    const AutoTile* GetAutoTile(int layerIndex, int x, int y) const;
    bool IsAutoTile(int layerIndex, int x, int y) const;

    // -----------------------------
    // Clear helpers
    // -----------------------------
    void ClearAnimatedTiles();
    void ClearAutoTiles();
    void ClearAllSpecialTiles();


private:
    int m_width = 0;
    int m_height = 0;
    int m_tileSize = 16;

    std::vector<Layer> m_layers;

    // Animated tiles registry: map position key -> AnimatedTile
    // key encoded as y * width + x + layerIndex * width*height
    std::unordered_map<uint64_t, AnimatedTile> m_animated;
    std::unordered_map<uint64_t, AutoTile> m_autotiles;

    // Internal helper
    sf::FloatRect TileUVRect(const Project::TileSetDescriptor& ds, int tileIndex) const;
    uint64_t EncodeKey(int layerIndex, int x, int y) const;
    void AppendTileQuad(sf::VertexArray& va, const sf::FloatRect& uv, const sf::Vector2f& pos, bool flipX, bool flipY, const sf::Texture* tex) const;
};

} // namespace Editor::Map

#endif // _EDITOR_TILEMAP_HPP__
