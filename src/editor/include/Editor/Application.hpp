#ifndef _EDITOR_APPLICATION_HPP__
#define _EDITOR_APPLICATION_HPP__

#include "Editor/Panel/PanelManager.hpp"
#include "Core/Application.hpp"
#include <imgui.h>
#include <imgui-SFML.h>

namespace Editor 
{
    class EditorApplication : public Core::Application
    {
    public:
        EditorApplication()
            : Core::Application(), m_panelManager(std::make_unique<PanelManager>(m_window, m_projectManager, m_entityManager)) {}
        ~EditorApplication() = default;
        
    private:
        void init() override;
        void handleEvents(const std::optional<sf::Event>& event) override;
        void update() override;
        void render() override;

        std::unique_ptr<PanelManager> m_panelManager;
        ImFont* m_font;
    };
}

#endif