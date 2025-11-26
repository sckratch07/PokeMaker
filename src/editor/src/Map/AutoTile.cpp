#include "Editor/Map/AutoTile.hpp"
#include <algorithm>

namespace Editor::Map {

void AutoTile::SetMapping(const std::vector<int>& mapping)
{
    m_mapping = mapping;
    // ensure capacity 256 (optional) - we don't force size but mapping index must be valid when used
}

uint8_t AutoTile::ComputeBitmask(const std::array<bool,8>& n)
{
    // Bit order: N(0), NE(1), E(2), SE(3), S(4), SW(5), W(6), NW(7)
    uint8_t mask = 0;
    for (size_t i = 0; i < 8; ++i) {
        if (n[i]) mask |= (1u << i);
    }
    return mask;
}

int AutoTile::ComputeVariant(const std::array<bool,8>& neighbors) const
{
    if (m_mapping.empty()) return -1;
    uint8_t mask = ComputeBitmask(neighbors);
    if (mask < m_mapping.size()) return m_mapping[mask];
    // if mapping smaller, fallback to mod
    return m_mapping[mask % m_mapping.size()];
}

bool AutoTile::HasMapping() const { return !m_mapping.empty(); }

} // namespace Editor::Map
