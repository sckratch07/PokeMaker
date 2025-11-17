#include <AutotileWFC.hpp>
#include <Logger.hpp>
#include <algorithm>
#include <limits>
#include <sstream>

namespace Engine
{
    AutotileWFC::AutotileWFC()
    {
        std::random_device rd;
        m_rng.seed(rd());
    }

    void AutotileWFC::setSeed(uint32_t s)
    {
        m_rng.seed(s);
    }

    void AutotileWFC::setRule(TileID tileId, Dir dir, const TileSet& allowed)
    {
        m_rules[tileId][static_cast<size_t>(dir)] = allowed;
    }

    bool AutotileWFC::loadRulesFromJson(const nlohmann::json& j)
    {
        try
        {
            m_rules.clear();
            for (auto it = j.begin(); it != j.end(); ++it)
            {
                TileID tid = std::stoi(it.key());
                const json& obj = it.value();
                std::array<TileSet, static_cast<size_t>(Dir::Count)> arr;
                auto loadDir = [&](const std::string& name, Dir d)
                {
                    if (obj.contains(name) && obj[name].is_array())
                    {
                        for (const json& v : obj[name])
                        {
                            arr[static_cast<size_t>(d)].insert(v.get<int>());
                        }
                    }
                };
                loadDir("up", Dir::Up);
                loadDir("right", Dir::Right);
                loadDir("down", Dir::Down);
                loadDir("left", Dir::Left);
                m_rules[tid] = std::move(arr);
            }
            return true;
        }
        catch (const std::exception& e)
        {
            Core::log(std::string("AutotileWFC::loadRulesFromJson failed: ") + e.what(), Core::LogLevel::Error);
            return false;
        }
    }

    void AutotileWFC::buildPermissiveRules(int tileCount)
    {
        m_rules.clear();
        TileSet all;
        for (int i = 0; i < tileCount; ++i) all.insert(i);
        for (int i = 0; i < tileCount; ++i)
        {
            std::array<TileSet, static_cast<size_t>(Dir::Count)> arr;
            for (size_t d = 0; d < arr.size(); ++d) arr[d] = all;
            m_rules[i] = std::move(arr);
        }
    }

    std::vector<AutotileWFC::Cell> AutotileWFC::makeInitialGrid(int w, int h, int tileCount) const {
        std::vector<Cell> grid;
        grid.resize(w * h);
        TileSet all;
        for (int t = 0; t < tileCount; ++t) all.insert(t);

        for (auto &c : grid)
        {
            c.possibilities = all;
            c.collapsed = false;
            c.value = -1;
        }
        return grid;
    }

    std::vector<std::pair<int,int>> AutotileWFC::neighbors4(int x, int y, int w, int h) const
    { 
        std::vector<std::pair<int,int>> res;
        if (y > 0) res.emplace_back(x, y - 1);        // Up
        if (x < w - 1) res.emplace_back(x + 1, y);    // Right
        if (y < h - 1) res.emplace_back(x, y + 1);    // Down
        if (x > 0) res.emplace_back(x - 1, y);        // Left
        return res;
    }

    int AutotileWFC::pickLowestEntropy(const std::vector<Cell>& grid)
    { 
        int bestIdx = -1;
        size_t bestEntropy = std::numeric_limits<size_t>::max();

        for (size_t i = 0; i < grid.size(); ++i)
        {
            if (grid[i].collapsed) continue;
            size_t s = grid[i].possibilities.size();
            if (s == 0) return static_cast<int>(i);
            if (s < bestEntropy)
            {
                bestEntropy = s;
                bestIdx = static_cast<int>(i);
            }
        }
        return bestIdx;
    }

    TileID AutotileWFC::pickRandomFromSet(const TileSet& s)
    {   
        if (s.empty()) return -1;
        std::uniform_int_distribution<size_t> dist(0, s.size() - 1);
        size_t idx = dist(m_rng);
        auto it = s.begin();
        std::advance(it, idx);
        return *it;
    }

    bool AutotileWFC::propagate(std::vector<Cell>& grid, int w, int h)
    {    
        bool changed = true;
        while (changed)
        {
            changed = false;

            for (int y = 0; y < h; ++y)
            {
                for (int x = 0; x < w; ++x)
                {
                    int idx = index(x,y,w);
                    Cell &cell = grid[idx];
                    if (cell.possibilities.empty()) return false;

                    TileSet newPoss;
                    for (TileID candidate : cell.possibilities)
                    {
                        bool okCandidate = true;

                        std::vector<std::pair<int,int>> neigh = neighbors4(x,y,w,h);
                        for (size_t ni = 0; ni < neigh.size(); ++ni)
                        {
                            int nx = neigh[ni].first;
                            int ny = neigh[ni].second;
                            int nidx = index(nx, ny, w);

                            Dir d;
                            if (ny == y - 1 && nx == x) d = Dir::Up;
                            else if (nx == x + 1 && ny == y) d = Dir::Right;
                            else if (ny == y + 1 && nx == x) d = Dir::Down;
                            else d = Dir::Left;

                            // allowed neighbor set according to rules for candidate
                            auto ruleIt = m_rules.find(candidate);
                            if (ruleIt == m_rules.end())
                                continue;

                            const TileSet& allowedForDir = ruleIt->second[static_cast<size_t>(d)];

                            bool neighborHas = false;
                            for (TileID np : grid[nidx].possibilities)
                            {
                                if (allowedForDir.find(np) != allowedForDir.end())
                                {
                                    neighborHas = true;
                                    break;
                                }
                            }
                            if (!neighborHas)
                            {
                            okCandidate = false;
                            break;
                            }
                        } // for neighbors
                        if (okCandidate) newPoss.insert(candidate);
                    } // for each candidate

                    if (newPoss.size() != cell.possibilities.size())
                    {
                        cell.possibilities = std::move(newPoss);
                        changed = true;
                        if (cell.possibilities.empty()) return false; // contradiction
                    }
                    // if exactly one possibility remains, mark collapsed
                    if (!cell.collapsed && cell.possibilities.size() == 1)
                    {
                        cell.collapsed = true;
                        cell.value = *cell.possibilities.begin();
                    }
                } // x
            } // y
        } // while changed
        return true;
    }

    void AutotileWFC::dumpGrid(const std::vector<Cell>& grid, int w, int h) const
    { 
        std::ostringstream oss;
        for (int y = 0; y < h; ++y)
        {
            for (int x = 0; x < w; ++x)
            {
                const Cell& c = grid[index(x,y,w)];
                if (c.collapsed) oss << c.value;
                else oss << ".";
                if (x < w - 1) oss << " ";
            }
            oss << "\n";
        }
        Core::log(oss.str(), Core::LogLevel::Info);
    }

    bool AutotileWFC::applyWFC(Tilemap& map, LayerType layerType, uint32_t seed, int maxAttempts, bool verbose)
    {   
        if (seed != 0) setSeed(seed);
        else
        {
            std::random_device rd;
            setSeed(rd());
        }

        int w = map.getWidth();
        int h = map.getHeight();
        if (w <= 0 || h <= 0)
        {
            Core::log("applyWFC: tilemap has no size", Core::LogLevel::Error);
            return false;
        }

        int tileCount = 0;
        if (map.getTileset()) tileCount = map.getTileset()->getTileCount();
        if (tileCount <= 0)
        {
            Core::log("applyWFC: tileset missing or empty, cannot run WFC", Core::LogLevel::Error);
            return false;
        }

        if (m_rules.empty())
        {
            buildPermissiveRules(tileCount);
            if (verbose) Core::log("AutotileWFC: no rules provided, using permissive rules.", Core::LogLevel::Warning);
        }

        int attempt = 0;
        while (attempt < maxAttempts)
        {
            ++attempt;
            std::vector<Cell> grid = makeInitialGrid(w, h, tileCount);

            bool ok = true;
            while (true)
            {
                int idx = pickLowestEntropy(grid);
                if (idx == -1) break;
                if (idx >= static_cast<int>(grid.size())) { ok = false; break; }

                TileID pick = pickRandomFromSet(grid[idx].possibilities);
                if (pick < 0) { ok = false; break; }
                grid[idx].possibilities.clear();
                grid[idx].possibilities.insert(pick);
                grid[idx].collapsed = true;
                grid[idx].value = pick;

                bool success = propagate(grid, w, h);
                if (!success) { ok = false; break; }
            }

            if (!ok)
            {
                if (verbose) Core::log("WFC attempt " + std::to_string(attempt) + " failed, retrying...", Core::LogLevel::Warning);
                continue;
            }

            Layer* layer = map.getLayer(layerType);
            if (!layer)
            {
                Core::log("applyWFC: layer not found", Core::LogLevel::Error);
                return false;
            }
            for (int y = 0; y < h; ++y)
            {
                for (int x = 0; x < w; ++x)
                {
                    const Cell& c = grid[index(x,y,w)];
                    TileID val = c.collapsed ? c.value : pickRandomFromSet(c.possibilities);
                    layer->setTile(x, y, static_cast<int>(val));
                }
            }

            if (verbose)
            {
                Core::log("WFC succeeded on attempt " + std::to_string(attempt), Core::LogLevel::Info);
                dumpGrid(grid, w, h);
            }
            return true;
        } // attempts
        Core::log("applyWFC: failed after max attempts", Core::LogLevel::Error);
        return false;
    }
} // namespace engine
