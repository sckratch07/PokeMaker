#ifndef _EDITOR_RUN_TAB_HPP__
#define _EDITOR_RUN_TAB_HPP__

#include <imgui.h>

namespace Editor::PanelTab
{
    void runTab()
    {
        if (ImGui::BeginMenu("Run"))
        {
            ImGui::EndMenu();
        }
    }

    void runShortcut(const std::optional<sf::Event>& event)
    {
        
    }
}

#endif