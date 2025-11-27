#ifndef _CORE_CONVERT_HPP__
#define _CORE_CONVERT_HPP__

#include "Core/TileMap.hpp"
#include <optional>

namespace Core
{
/**
 * @brief Convertit une TileMap provenant de l'éditeur en une TileMap "runtime"
 * 
 * Cette fonction prend une TileMap créée ou modifiée dans l'éditeur et la
 * transforme en une version adaptée à l'utilisation dans le moteur de jeu.
 * 
 * @param editorMap La TileMap provenant de l'éditeur
 * @return TileMap La TileMap convertie prête à être utilisée dans le jeu
 */
TileMap ConvertEditorTileMapToTileMapData(const TileMap& editorMap) noexcept;

/**
 * @brief Résout les tilesets d'une TileMap selon une liste autorisée
 * 
 * Cette fonction vérifie que chaque tileset utilisé dans la TileMap est bien
 * présent dans la liste des identifiants de tilesets autorisés. Les tilesets
 * non autorisés peuvent être remplacés ou ignorés selon l'implémentation.
 * 
 * @param map La TileMap dont les tilesets doivent être résolus
 * @param allowedTilesetIds Liste des identifiants de tilesets autorisés
 * @return bool Retourne true si tous les tilesets ont été correctement résolus, false sinon
 */
bool ResolveTilesets(TileMap& map, const std::vector<std::string>& allowedTilesetIds) noexcept;

/**
 * @brief Normalise les indices de tiles dans une TileMap
 * 
 * Cette fonction ajuste les indices des tiles pour s'assurer qu'ils sont
 * cohérents et valides. Cela peut inclure :
 * - Réindexation des tiles pour éviter des indices manquants
 * - Ajustement des références aux tilesets
 * - Préparation de la TileMap pour l'export ou le runtime
 * 
 * @param map La TileMap à normaliser
 */
void NormalizeTileIndices(TileMap& map) noexcept;

} // namespace Core

#endif
