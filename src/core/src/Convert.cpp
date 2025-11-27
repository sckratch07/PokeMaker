#include "Core/Convert.hpp"
#include <algorithm>

namespace Core
{
TileMap ConvertEditorTileMapToTileMapData(const TileMap& editorMap) noexcept
{
    TileMap out = editorMap;
    std::vector<std::string> allowed;
    allowed.reserve(out.tilesets.size());
    for (const auto &ts : out.tilesets) allowed.push_back(ts.id);
    ResolveTilesets(out, allowed);
    NormalizeTileIndices(out);
    return out;
}

bool ResolveTilesets(TileMap& map, const std::vector<std::string>& allowedTilesetIds) noexcept
{
    bool all_valid = true;
    auto exists = [&allowedTilesetIds](const std::string &id)
    {
        return std::find(allowedTilesetIds.begin(), allowedTilesetIds.end(), id) != allowedTilesetIds.end();
    };
    for (auto &layer : map.layers)
    {
        if (layer.type != LayerType::TileLayer) continue;
        for (auto &tile : layer.tiles)
        {
            if (tile.tileset_id.empty()) continue;
            if (!exists(tile.tileset_id))
            {
                tile.tileset_id.clear();
                tile.tile_index = -1;
                tile.frames.clear();
                all_valid = false;
            }
            else
            {
                for (auto &f : tile.frames)
                {
                    if (!exists(f.tileset_id))
                    {
                        f.tileset_id.clear();
                        f.tile_index = -1;
                    }
                }
            }
        }
    }
    return all_valid;
}

void NormalizeTileIndices(TileMap& map) noexcept
{
    for (auto &layer : map.layers)
    {
        if (layer.type != LayerType::TileLayer) continue;
        for (auto &tile : layer.tiles)
        {
            if (tile.tile_index < 0) tile.tile_index = -1;
            for (auto &f : tile.frames)
            {
                if (f.tile_index < 0) f.tile_index = -1;
            }
        }
    }
}
} // namespace core
