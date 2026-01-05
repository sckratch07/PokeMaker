#ifndef _EDITOR_HELP_TAB_HPP__
#define _EDITOR_HELP_TAB_HPP__

#include <imgui.h>
#include <shellapi.h>

namespace Editor::PanelTab
{
    void helpTab()
    {
        if (ImGui::BeginMenu("Help"))
        {
            if (ImGui::MenuItem("Documentation"))
            {
                ShellExecuteA(NULL, NULL, "http://www.cplusplus.com", NULL, NULL, SW_SHOWNORMAL);
            }
            ImGui::EndMenu();
        }
    }
}

#endif