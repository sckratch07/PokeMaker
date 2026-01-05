#ifndef _EDITOR_PROJECT_TAB_HPP__
#define _EDITOR_PROJECT_TAB_HPP__

#include "Core/ProjectManager.hpp"
#include <SFML/Graphics.hpp>
#include <portable-file-dialogs.h>
#include <imgui.h>

namespace Editor::PanelTab
{
    void projectTab(std::shared_ptr<Core::ProjectManager>& projectManager)
    {
        bool activeProject = projectManager->getProject() != nullptr;
        if (ImGui::BeginMenu("Project"))
        {
            if (ImGui::MenuItem("New Project", "Ctrl + N"))
            {
                auto dir = pfd::select_folder("Select a project directory", "../").result();
                if (!dir.empty())
                    projectManager->createNewProject(std::filesystem::path(dir).stem().string(), dir);
            }
            if (ImGui::MenuItem("Open Project", "Ctrl + O"))
            {
                auto dir = pfd::select_folder("Select a project directory", "../").result();
                if (!dir.empty())
                    projectManager->loadProject(dir);
            }
            if (ImGui::MenuItem("Save Project", "Ctrl + S", false, activeProject))
            {
                projectManager->saveProject();
            }
            if (ImGui::MenuItem("Close Project", "Ctrl + K", false, activeProject))
            {
                projectManager->closeProject();
            }
            ImGui::EndMenu();
        }
    }

    void shortcutProject(const std::optional<sf::Event>& event, std::shared_ptr<Core::ProjectManager>& projectManager)
    {
        if (const auto* key = event->getIf<sf::Event::KeyPressed>())
        {
            if (key->control)
            {
                if (key->scancode == sf::Keyboard::Scancode::N)
                {
                    auto dir = pfd::select_folder("Select a project directory", "../").result();
                    if (!dir.empty())
                        projectManager->createNewProject(std::filesystem::path(dir).stem().string(), dir);
                }
                else if (key->scancode == sf::Keyboard::Scancode::O)
                {
                    auto dir = pfd::select_folder("Select a project directory", "../").result();
                    if (!dir.empty())
                        projectManager->loadProject(dir);
                }
                else if (key->scancode == sf::Keyboard::Scancode::S && projectManager->getProject())
                {
                    projectManager->saveProject();
                }
                else if (key->scancode == sf::Keyboard::Scancode::K && projectManager->getProject())
                {
                    projectManager->closeProject();
                }
            }
        }
    }
}

#endif