#include "Core/Tile.hpp"

namespace Core
{
void to_json(nlohmann::json& j, const TileFrame& f)
{
    j = nlohmann::json
    {
        {"tileset", f.tileset_id},
        {"tile_index", f.tile_index},
        {"duration_ms", f.duration_ms}
    };
}

void from_json(const nlohmann::json& j, TileFrame& f)
{
    f.tileset_id = j.value("tileset", std::string());
    f.tile_index = j.value("tile_index", -1);
    f.duration_ms = j.value("duration_ms", 100);
}

void to_json(nlohmann::json& j, const Tile& t)
{
    j = nlohmann::json::object();
    j["tileset"] = t.tileset_id;
    j["tile_index"] = t.tile_index;
    if (!t.properties.empty()) j["properties"] = t.properties;
    if (!t.frames.empty())
    {
        j["animated"] = nlohmann::json::array();
        for (const auto &f : t.frames) j["animated"].push_back(f);
        j["loop"] = t.loop;
    }
}

void from_json(const nlohmann::json& j, Tile& t)
{
    t.tileset_id = j.value("tileset", std::string());
    t.tile_index = j.value("tile_index", -1);
    if (j.contains("properties") && j["properties"].is_object())
    {
        t.properties = j["properties"].get<std::map<std::string, nlohmann::json>>();
    }
    else
    {
        t.properties.clear();
    }
    t.frames.clear();
    if (j.contains("animated") && j["animated"].is_array())
    {
        for (const auto &elem : j["animated"])
        {
            TileFrame f;
            from_json(elem, f);
            t.frames.push_back(f);
        }
        t.loop = j.value("loop", true);
    }
    else
    {
        t.loop = true;
    }
}

} // namespace core
