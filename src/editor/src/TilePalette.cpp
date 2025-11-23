#include "Editor/TilePalette.hpp"
#include <imgui.h>

namespace Editor {

TilePalette::TilePalette()
    : m_tileWidth(0)
    , m_tileHeight(0)
    , m_spacing(0)
    , m_selected(-1)
{
}

TilePalette::~TilePalette() = default;

bool TilePalette::loadFromFile(const std::string& path, int tileWidth, int tileHeight, int spacing)
{
    m_tileWidth = tileWidth;
    m_tileHeight = tileHeight;
    m_spacing = spacing;

    if (!m_texture.loadFromFile(path)) {
        return false;
    }

    m_tiles.clear();

    int texW = static_cast<int>(m_texture.getSize().x);
    int texH = static_cast<int>(m_texture.getSize().y);

    // calculer colonnes/rows en tenant compte spacing
    int columns = (m_tileWidth + m_spacing) > 0 ? texW / (m_tileWidth + m_spacing) : 0;
    int rows = (m_tileHeight + m_spacing) > 0 ? texH / (m_tileHeight + m_spacing) : 0;

    for (int y = 0; y < rows; ++y) {
        for (int x = 0; x < columns; ++x) {
            int px = x * (m_tileWidth + m_spacing);
            int py = y * (m_tileHeight + m_spacing);
            m_tiles.emplace_back(sf::IntRect({px, py}, {m_tileWidth, m_tileHeight}));
        }
    }
    return true;
}

void TilePalette::render()
{
    if (m_tiles.empty()) {
        ImGui::TextUnformatted("Aucune tuile chargée.");
        return;
    }

    ImGui::Text("Sélectionnez une tuile:");
    const float thumbSize = 32.0f;
    int cols = 8;
    for (size_t i = 0; i < m_tiles.size(); ++i)
    {
        if (i % cols != 0) ImGui::SameLine();

        // conversion SFML texture -> ImTextureID dépend de binding. ImGui-SFML fournit souvent ImTextureID via texture.getNativeHandle()
        ImTextureID id = (ImTextureID)m_texture.getNativeHandle();

        // ImGui::Image prend ImTextureID et les UVs peuvent être fournis si nécessaire - on va afficher toute la texture en thumb
        // pour garder la démo simple ; les tuiles individuelles seront utilisées par le visualiseur de map (sprite cropping).
        ImGui::Image(id, ImVec2(thumbSize, thumbSize));

        if (ImGui::IsItemClicked()) {
            m_selected = static_cast<int>(i);
        }
        if (m_selected == static_cast<int>(i)) {
            ImGui::SameLine();
            ImGui::Text("[X]");
        }
    }
}

int TilePalette::selectedTile() const
{
    return m_selected;
}

/* ---------- NOUVEAUX ACCESSEURS ---------- */

const sf::Texture* TilePalette::texture() const
{
    return &m_texture;
}

const std::vector<sf::IntRect>& TilePalette::tiles() const
{
    return m_tiles;
}

int TilePalette::tileCount() const
{
    return static_cast<int>(m_tiles.size());
}

} // namespace Editor
