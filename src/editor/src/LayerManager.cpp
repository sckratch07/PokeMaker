#include "Editor/LayerManager.hpp"
#include <imgui.h>

namespace Editor {

LayerManager::LayerManager()
    : m_selected(-1)
{
    // Calque par défaut
    addLayer("Background");
    addLayer("Midground");
    addLayer("Foreground");
}

LayerManager::~LayerManager() = default;

void LayerManager::addLayer(const std::string& name)
{
    Layer l;
    l.name = name.empty() ? ("Layer " + std::to_string(m_layers.size())) : name;
    m_layers.push_back(l);
}

void LayerManager::removeLayer(int index)
{
    if (index < 0 || index >= static_cast<int>(m_layers.size())) return;
    m_layers.erase(m_layers.begin() + index);
    m_selected = -1;
}

void LayerManager::moveLayerUp(int index)
{
    if (index <= 0 || index >= static_cast<int>(m_layers.size())) return;
    std::swap(m_layers[index], m_layers[index - 1]);
}

void LayerManager::moveLayerDown(int index)
{
    if (index < 0 || index >= static_cast<int>(m_layers.size()) - 1) return;
    std::swap(m_layers[index], m_layers[index + 1]);
}

void LayerManager::render()
{
    if (ImGui::Button("Ajouter calque")) { addLayer("New Layer"); }
    ImGui::SameLine();
    if (ImGui::Button("Supprimer") && m_selected >= 0) { removeLayer(m_selected); }

    ImGui::Separator();
    for (int i = static_cast<int>(m_layers.size()) - 1; i >= 0; --i)
    {
        ImGui::PushID(i);
        Layer& l = m_layers[i];
        if (ImGui::Selectable(l.name.c_str(), m_selected == i)) {
            m_selected = i;
        }
        ImGui::SameLine();
        ImGui::Checkbox(("V##" + std::to_string(i)).c_str(), &l.visible);
        ImGui::SameLine();
        if (ImGui::Button(("Up##" + std::to_string(i)).c_str())) moveLayerUp(i);
        ImGui::SameLine();
        if (ImGui::Button(("Down##" + std::to_string(i)).c_str())) moveLayerDown(i);
        ImGui::PopID();
    }
}

} // namespace Editor
