#ifndef _EDITOR_PROJECT_TAB_HPP__
#define _EDITOR_PROJECT_TAB_HPP__

#include "Core/ProjectManager.hpp"
#include <imgui.h>

namespace Editor
{
    namespace PanelTab
    {
        void Project(std::shared_ptr<Core::ProjectManager>& projectManager)
        {
            bool activeProject = projectManager->getProject() != nullptr;
            if (ImGui::BeginMainMenuBar())
            {
                if (ImGui::BeginMenu("Project"))
                {
                    if (ImGui::MenuItem("New Project", "Ctrl + N"))
                    {
                        
                    }
                    if (ImGui::MenuItem("Open Project", "Ctrl + O"))
                    {
                        
                    }
                    if (activeProject)
                    {   
                        if (ImGui::MenuItem("Save Project", "Ctrl + S"))
                        {
                            projectManager->saveProject();
                        }
                        if (ImGui::MenuItem("Close Project", "Ctrl + K"))
                        {
                            projectManager->closeProject();
                        }
                    }        
                }
            }
            ImGui::EndMainMenuBar();
        }
    }
}

#endif