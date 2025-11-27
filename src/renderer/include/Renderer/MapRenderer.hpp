#pragma once

#include "Core/TileMap.hpp"
#include "Core/TileSet.hpp"
#include "Core/ResourceManager.hpp"
#include <SFML/Graphics.hpp>
#include <string>
#include <unordered_map>

namespace Renderer
{
/**
 * @brief Classe responsable du rendu d'une TileMap.
 *
 * MapRenderer ne modifie pas la TileMap. Il prend en charge :
 * - l'affichage des tiles statiques et animées
 * - l'application de textures provenant de Core::TileSet
 * - le rendu layer par layer dans l'ordre défini dans la TileMap
 *
 * Le MapRenderer est indépendant de l'Editor mais peut être utilisé pour l'aperçu.
 */
class MapRenderer
{
public:
    MapRenderer();
    ~MapRenderer() = default;

    /**
     * @brief Définit la TileMap à rendre.
     * @param map référence constante vers la TileMap
     */
    void SetTileMap(const Core::TileMap& map);

    /**
     * @brief Met à jour l'animation des tiles (doit être appelée chaque frame).
     * @param deltaTime durée écoulée depuis la dernière frame en secondes
     */
    void Update(float deltaTime);

    /**
     * @brief Rend la TileMap sur la fenêtre SFML donnée.
     * @param target fenêtre ou render target SFML
     */
    void Render(sf::RenderTarget& target);

    /**
     * @brief Définit le gestionnaire de ressources pour charger les textures des tilesets.
     * @param manager pointeur vers ResourceManager<sf::Texture>
     */
    void SetTextureManager(Core::ResourceManager<sf::Texture>* manager);

private:
    const Core::TileMap* m_tileMap = nullptr;  /**< TileMap à rendre */
    Core::ResourceManager<sf::Texture>* m_textureManager = nullptr; /**< Gestionnaire de textures */

    struct TileDrawData
    {
        TileDrawData() = default;

        sf::Sprite sprite;
        size_t currentFrame = 0;
        float frameTimer = 0.0f;
    };

    std::unordered_map<const Core::Tile*, TileDrawData> m_tileDrawData; /**< Données animées pour chaque tile */

    /**
     * @brief Met à jour le sprite correspondant à une tile animée.
     * @param tile référence vers la tile
     * @param data référence vers les données de rendu de la tile
     * @param deltaTime temps écoulé depuis la dernière frame
     */
    void UpdateTileAnimation(const Core::Tile& tile, TileDrawData& data, float deltaTime);

    /**
     * @brief Crée le sprite SFML pour une tile statique ou animée.
     * @param tile référence vers la tile
     * @return Sprite SFML prêt à être rendu
     */
    sf::Sprite CreateTileSprite(const Core::Tile& tile) const;

    /**
     * @brief Récupère la texture SFML correspondant à un tileset
     */
    sf::Texture* GetTextureForTileset(const std::string& tilesetId) const;
};

} // namespace renderer
