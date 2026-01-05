#ifndef _EDITOR_HELP_TAB_HPP__
#define _EDITOR_HELP_TAB_HPP__

#include "Core/ProjectManager.hpp"
#include <imgui.h>
#include <shellapi.h>

namespace Editor::PanelTab::HelpTab
{
    void tab()
    {
        if (ImGui::BeginMenu("Help"))
        {
            if (ImGui::MenuItem("Documentation"))
            {
                ShellExecuteA( NULL, NULL, "http://www.cplusplus.com", NULL, NULL, SW_SHOWNORMAL );
            }
            ImGui::EndMenu();
        }
    }

    void handleEvents(const std::optional<sf::Event>& event, std::shared_ptr<Core::ProjectManager>& projectManager)
    {
        
    }
}

#endif