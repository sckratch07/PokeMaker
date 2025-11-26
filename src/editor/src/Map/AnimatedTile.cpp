#include "Editor/Map/AnimatedTile.hpp"

namespace Editor::Map {

void AnimatedTile::AddFrame(const Tile& tile, float durationSeconds)
{
    if (durationSeconds <= 0.0f) durationSeconds = 0.1f;
    m_frames.push_back(tile);
    m_durations.push_back(durationSeconds);
}

void AnimatedTile::Clear()
{
    m_frames.clear();
    m_durations.clear();
    m_current = 0;
    m_elapsed = 0.0f;
}

void AnimatedTile::Update(float dtSeconds)
{
    if (m_frames.empty()) return;
    m_elapsed += dtSeconds;
    while (m_elapsed >= m_durations[m_current])
    {
        m_elapsed -= m_durations[m_current];
        m_current = (m_current + 1) % m_frames.size();
    }
}

Tile AnimatedTile::GetCurrentTile() const
{
    if (m_frames.empty()) return Tile();
    return m_frames[m_current];
}

void AnimatedTile::Reset()
{
    m_current = 0;
    m_elapsed = 0.f;
}

bool AnimatedTile::IsValid() const
{
    return !m_frames.empty();
}

} // namespace Editor::Map
