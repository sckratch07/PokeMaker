#ifndef _RENDERER_TILEATLAS_HPP__
#define _RENDERER_TILEATLAS_HPP__

#include "Core/ResourceManager.hpp"
#include "Core/TileSet.hpp"
#include <SFML/Graphics.hpp>
#include <string>
#include <unordered_map>
#include <memory>
#include <vector>
#include <optional>

namespace Renderer
{
/**
* @brief Gestion d'atlas de tiles (association TileSet -> sf::Texture).
*
* TileAtlas utilise le ResourceManager générique (depuis Core) pour charger
* des sf::Texture et fournit des utilitaires pour récupérer la sous-rect
* (sf::IntRect) correspondant à un tile index dans un tileset.
*/
class TileAtlas
{
public:
    using TexturePtr = std::shared_ptr<sf::Texture>;

    TileAtlas();

    /**
    * @brief Enregistre un tileset (métadonnées). N'en charge pas la texture tant
    * que LoadTextureForTileset n'est pas appelé.
    */
    void RegisterTileSet(const Core::TileSet& tileset);

    /**
    * @brief Charge la texture pour un tileset donné (par id). Retourne faux si
    * le tileset n'est pas enregistré ou si le chargement échoue.
    */
    bool LoadTextureForTileset(const std::string& tilesetId);

    /**
    * @brief Récupère la texture associée à un tileset (ou nullptr si absente).
    */
    TexturePtr GetTexture(const std::string& tilesetId) const noexcept;

    /**
    * @brief Calcule la sous-rectangle (IntRect) d'un tile_index dans le tileset.
    * @return std::nullopt si tileset inconnu.
    */
    std::optional<sf::IntRect> GetTileRect(const std::string& tilesetId, int tileIndex) const noexcept;

    /**
    * @brief Retourne la liste des tileset ids enregistrés.
    */
    std::vector<std::string> GetRegisteredIds() const;

private:
    Core::ResourceManager<sf::Texture> m_textureManager; /**< charge et cache les textures */
    std::unordered_map<std::string, Core::TileSet> m_tilesets; /**< métadonnées */
};
} // namespace renderer

#endif