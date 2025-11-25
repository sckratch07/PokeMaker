#include "Editor/AutoTile.hpp"
#include "Editor/TileLayer.hpp"
#include "Editor/Tile.hpp"

namespace Editor {

// ------------------------
// Gestion des règles
// ------------------------

void AutoTile::SetRule(uint8_t mask, uint32_t tileId)
{
    m_rules[mask] = tileId;
}

void AutoTile::RemoveRule(uint8_t mask)
{
    m_rules.erase(mask);
}

void AutoTile::Clear()
{
    m_rules.clear();
}

uint32_t AutoTile::Resolve(uint8_t mask) const
{
    auto it = m_rules.find(mask);
    if (it != m_rules.end())
        return it->second;
    return 0; // aucun autotile correspondant
}

// ------------------------
// Calcul du mask 8 directions
// ------------------------

uint8_t AutoTile::ComputeMask(const TileLayer& layer, unsigned x, unsigned y) const
{
    const Tile* baseTile = layer.GetTile(x, y);
    if (!baseTile || baseTile->IsEmpty())
        return 0;

    const uint32_t targetId = baseTile->id;
    uint8_t mask = 0;

    auto check = [&](int ox, int oy, uint8_t bit)
    {
        const Tile* t = layer.GetTile(x + ox, y + oy);
        if (t && t->id == targetId)
            mask |= bit;
    };

    // directions :
    check(0, -1,   1);   // N
    check(1, -1,   2);   // NE
    check(1, 0,    4);   // E
    check(1, 1,    8);   // SE
    check(0, 1,    16);  // S
    check(-1, 1,   32);  // SW
    check(-1, 0,   64);  // W
    check(-1, -1,  128); // NW

    return mask;
}

// ------------------------
// Application auto-tile
// ------------------------

void AutoTile::ApplyToTile(TileLayer& layer, unsigned x, unsigned y)
{
    Tile* t = layer.GetTile(x, y);
    if (!t || t->IsEmpty())
        return;

    t->AddFlag(TileFlags::TILEFLAG_AUTOTILE);

    uint8_t mask = ComputeMask(layer, x, y);
    t->autoTileMask = mask;

    uint32_t resolved = Resolve(mask);
    if (resolved != 0)
        t->id = resolved;
}

void AutoTile::ApplyToLayer(TileLayer& layer)
{
    for (unsigned y = 0; y < layer.size.y; ++y)
    {
        for (unsigned x = 0; x < layer.size.x; ++x)
        {
            ApplyToTile(layer, x, y);
        }
    }
}

} // namespace Editor
