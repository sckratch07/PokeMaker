#ifndef _RENDERER_MAPRENDERER_HPP__
#define _RENDERER_MAPRENDERER_HPP__

#include "Core/TileMap.hpp"
#include "Renderer/TileAtlas.hpp"
#include <SFML/Graphics.hpp>

namespace Renderer
{
/**
* @brief MapRenderer : dessine un core::TileMap en batchant par tileset.
*
* - Ne modifie pas les données Core (const où possible) ;
* - Supporte l'animation basique (Update(dt)) en utilisant les frames définies
* dans core::Tile::frames ;
* - Effectue un culling selon la vue fournie par SetView ;
* - Groupes d'vertex par texture pour réduire les draw calls.
*/
class MapRenderer
{
public:
    MapRenderer();
    ~MapRenderer();

    /**
    * @brief Définit la TileMap à rendre. La carte est copiée localement pour
    * permettre des opérations (ex : conversion, normalisation) sans toucher
    * aux données source.
    */
    void SetTileMap(const Core::TileMap& map);

    /**
    * @brief Définit la vue courante utilisée pour le culling et le calcul des
    * coordonnées de rendu.
    */
    void SetView(const sf::View& view) noexcept;

    /**
    * @brief Met à jour l'état interne (animations). dt en secondes.
    */
    void Update(float dt) noexcept;

    /**
    * @brief Dessine la map sur la cible donnée.
    */
    void Draw(sf::RenderTarget& target);

    /**
    * @brief Accède au TileAtlas (pour précharger des textures depuis l'extérieur).
    */
    TileAtlas& Atlas() noexcept { return m_atlas; }

private:
    Core::TileMap m_map; /**< copie locale de la TileMap */
    TileAtlas m_atlas; /**< atlas gère les textures */
    sf::View m_view; /**< vue utilisée pour culling */

    // Animation state per tile (parallel aux layers.tiles)
    std::vector<std::vector<int>> m_frameIndices; // layer -> tile index -> current frame index
    std::vector<std::vector<float>> m_frameTimers; // layer -> tile index -> elapsed ms

    // Internal helpers
    void EnsureAnimationStateExists();
    void BuildAndDrawBatches(sf::RenderTarget& target);
    void DrawTileQuad(sf::VertexArray& va, int vx, int vy, const sf::IntRect& srcRect, const sf::Texture* tex);
};

} // namespace renderer

#endif