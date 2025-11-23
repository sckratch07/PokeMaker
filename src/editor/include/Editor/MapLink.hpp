#ifndef _EDITOR_MAPLINK_HPP__
#define _EDITOR_MAPLINK_HPP__

/**
 * @file MapLink.hpp
 * @brief Lien de transition entre deux maps.
 */

#include <nlohmann/json.hpp>
#include <string>

namespace Editor {

struct MapLink
{
    std::string targetMapName;
    int fromX = 0;
    int fromY = 0;
    int toX = 0;
    int toY = 0;

    nlohmann::json toJson() const;
    void fromJson(const nlohmann::json& j);
};

} // namespace Editor

#endif
