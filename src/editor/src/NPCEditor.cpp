#include "Editor/NPCEditor.hpp"
#include <imgui.h>

namespace Editor {

NPCEditor::NPCEditor()
    : m_selected(-1)
{
    // Exemple de PNJ par défaut
    m_npcs.push_back({"Sacha", 5, 3, 10});
    m_npcs.push_back({"Ondine", 12, 7, 8});
}

NPCEditor::~NPCEditor() = default;

void NPCEditor::render()
{
    if (ImGui::Button("Ajouter PNJ")) {
        addNPC({"Nouvel NPC", 0, 0, 1});
    }

    ImGui::Separator();

    for (size_t i = 0; i < m_npcs.size(); ++i)
    {
        ImGui::PushID(static_cast<int>(i));
        if (ImGui::Selectable(m_npcs[i].name.c_str(), m_selected == static_cast<int>(i))) {
            m_selected = static_cast<int>(i);
        }
        if (m_selected == static_cast<int>(i)) {
            ImGui::InputText("Nom", &m_npcs[i].name[0], 64); // Pour demo simple (attention)
            ImGui::InputInt("X", &m_npcs[i].x);
            ImGui::InputInt("Y", &m_npcs[i].y);
            ImGui::InputInt("Niveau", &m_npcs[i].level);
        }
        ImGui::PopID();
    }
}

void NPCEditor::addNPC(const NPCData& npc)
{
    m_npcs.push_back(npc);
}

} // namespace Editor
