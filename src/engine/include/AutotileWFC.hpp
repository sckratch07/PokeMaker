#ifndef _ENGINE_AUTOTILE_WFC_HPP__
#define _ENGINE_AUTOTILE_WFC_HPP__

#include <Tilemap.hpp>
#include <nlohmann/json.hpp>
#include <random>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using json = nlohmann::json;

namespace Engine
{
    enum class Dir
    {
        Up = 0,
        Right = 1,
        Down = 2,
        Left = 3,
        Count = 4
    };

    inline int oppositeDir(Dir d)
    {
        return (static_cast<int>(d) + 2) % 4;
    }

    using TileID = int;
    using TileSet = std::unordered_set<TileID>;

    // adjacency rules: rules[tileId][dir] = set of allowed neighbor tile ids on that side
    using AdjRules = std::unordered_map<TileID, std::array<TileSet, static_cast<size_t>(Dir::Count)>>;

    class AutotileWFC
    {
    public:
        AutotileWFC();
        ~AutotileWFC() = default;

        // --- Rules management ---
        // define allowed neighbors for (tileId) when looking in direction dir
        void setRule(TileID tileId, Dir dir, const TileSet& allowed);
        // load rules from JSON of form:
        // { "<tileId>": { "up": [..], "right": [...], "down": [...], "left":[...] }, ... }
        bool loadRulesFromJson(const json& j);

        // If no rules provided, this builds a permissive rule: every tile allowed next to every tile.
        void buildPermissiveRules(int tileCount);

        // --- WFC execution ---
        // apply WFC to the given map layer. Returns true on success, false on failure (after maxAttempts).
        bool applyWFC(Tilemap& map, LayerType layerType, uint32_t seed = 0, int maxAttempts = 10, bool verbose = false);

        // helper: set random engine seed
        void setSeed(uint32_t s);

    private:
        struct Cell
        {
           TileSet possibilities;
           bool collapsed = false;
           TileID value = -1;
        };

        AdjRules m_rules;
        std::mt19937 m_rng;

        // utilities
        std::vector<Cell> makeInitialGrid(int w, int h, int tileCount) const;
        bool propagate(std::vector<Cell>& grid, int w, int h);
        int index(int x, int y, int w) const { return y * w + x; }
        std::vector<std::pair<int,int>> neighbors4(int x, int y, int w, int h) const;

        // pick cell with lowest entropy (>1). returns index or -1 if all collapsed.
        int pickLowestEntropy(const std::vector<Cell>& grid);
        TileID pickRandomFromSet(const TileSet& s);

        // debug
        void dumpGrid(const std::vector<Cell>& grid, int w, int h) const;
    };
} // namespace Engine

#endif
