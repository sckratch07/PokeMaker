#ifndef _EDITOR_MAP_HPP__
#define _EDITOR_MAP_HPP__

#include "MapLink.hpp"
#include "LayerManager.hpp"
#include <nlohmann/json.hpp>
#include <string>
#include <vector>

/**
 * @file Map.hpp
 * @brief Représente une map éditable : layers, dimensions, liens vers d'autres maps.
 */

namespace Editor {

class Map
{
public:
    Map();
    Map(const std::string& name, int width, int height);

    std::string name;
    int width;
    int height;

    /** @brief Layers de la map */
    std::vector<Layer> layers;

    /** @brief Liens vers d'autres maps */
    std::vector<MapLink> links;

    /** @brief Convertit la map vers JSON */
    nlohmann::json toJson() const;

    /** @brief Charge la map depuis un JSON */
    void fromJson(const nlohmann::json& j);
};

} // namespace Editor

#endif
