#include "Editor/WFCGenerator.hpp"
#include <algorithm>
#include <numeric>
#include <stdexcept>

namespace Editor {

WFCGenerator::WFCGenerator()
    : m_rng(std::random_device{}()), m_seedSet(false)
{
}

WFCGenerator::~WFCGenerator() = default;

void WFCGenerator::setSeed(std::optional<unsigned int> seed)
{
    if (seed.has_value()) {
        m_rng.seed(seed.value());
    } else {
        m_rng.seed(std::random_device{}());
    }
    m_seedSet = true;
}

void WFCGenerator::addRule(const TileRule& rule)
{
    m_rules.push_back(rule);
    m_ruleMap[rule.id] = rule;
}

// Helper: sélection pondérée d'une tuile parmi candidates
int weightedRandomTile(const std::vector<TileRule>& candidates, std::mt19937& rng)
{
    float totalWeight = 0.0f;
    for (const auto& c : candidates) totalWeight += c.weight;

    std::uniform_real_distribution<float> dist(0.0f, totalWeight);
    float r = dist(rng);
    for (const auto& c : candidates) {
        if (r < c.weight) return c.id;
        r -= c.weight;
    }
    return candidates.front().id; // fallback
}

std::vector<int> WFCGenerator::generate(int width, int height)
{
    if (m_rules.empty()) throw std::runtime_error("Aucune règle définie pour WFCGenerator.");

    std::vector<int> map(width * height, -1);

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {

            std::vector<TileRule> candidates = m_rules;

            // Filtrage selon voisin haut
            if (y > 0) {
                int upTile = map[(y-1) * width + x];
                auto it = m_ruleMap.find(upTile);
                if (it != m_ruleMap.end()) {
                    auto allowed = it->second.neighbors.find("down");
                    if (allowed != it->second.neighbors.end()) {
                        std::vector<TileRule> filtered;
                        for (auto& c : candidates) {
                            if (std::find(allowed->second.begin(), allowed->second.end(), c.id) != allowed->second.end()) {
                                filtered.push_back(c);
                            }
                        }
                        if (!filtered.empty()) candidates = filtered;
                    }
                }
            }

            // Filtrage selon voisin gauche
            if (x > 0) {
                int leftTile = map[y * width + (x-1)];
                auto it = m_ruleMap.find(leftTile);
                if (it != m_ruleMap.end()) {
                    auto allowed = it->second.neighbors.find("right");
                    if (allowed != it->second.neighbors.end()) {
                        std::vector<TileRule> filtered;
                        for (auto& c : candidates) {
                            if (std::find(allowed->second.begin(), allowed->second.end(), c.id) != allowed->second.end()) {
                                filtered.push_back(c);
                            }
                        }
                        if (!filtered.empty()) candidates = filtered;
                    }
                }
            }

            // Sélection pondérée
            int selected = weightedRandomTile(candidates, m_rng);
            map[y * width + x] = selected;
        }
    }

    return map;
}

} // namespace Editor
