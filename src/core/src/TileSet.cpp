#include "Core/TileSet.hpp"

namespace Core
{
void to_json(nlohmann::json& j, const TileSet& t)
{
    j = nlohmann::json
    {
        {"id", t.id},
        {"path", t.path},
        {"tile_width", t.tile_width},
        {"tile_height", t.tile_height},
        {"columns", t.columns}
    };
}

void from_json(const nlohmann::json& j, TileSet& t)
{
    t.id = j.value("id", std::string());
    t.path = j.value("path", std::string());
    t.tile_width = j.value("tile_width", 32);
    t.tile_height = j.value("tile_height", 32);
    t.columns = j.value("columns", 0);
}
} // namespace core
