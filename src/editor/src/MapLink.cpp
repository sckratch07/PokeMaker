#include "Editor/MapLink.hpp"

namespace Editor {

nlohmann::json MapLink::toJson() const
{
    return {
        {"target", targetMapName},
        {"from", {fromX, fromY}},
        {"to",   {toX, toY}}
    };
}

void MapLink::fromJson(const nlohmann::json& j)
{
    targetMapName = j.at("target").get<std::string>();

    fromX = j.at("from")[0];
    fromY = j.at("from")[1];
    toX = j.at("to")[0];
    toY = j.at("to")[1];
}

} // namespace Editor
