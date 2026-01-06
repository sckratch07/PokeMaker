#include "Editor/Application.hpp"
#include <filesystem>
#include <iostream>

namespace Editor
{
    void EditorApplication::init()
    {
        m_window.setVerticalSyncEnabled(true);
        m_window.setFramerateLimit(60);
        m_window.setIcon(sf::Image("../resources/icon.png"));

        ImGui::CreateContext();


        if (ImGui::SFML::Init(m_window))
        {
            ImGuiIO& io = ImGui::GetIO();
            ImGuiStyle& style = ImGui::GetStyle();
            ImVec4* colors = style.Colors;

            // ======= Arrondis & espacements =======
            style.WindowRounding    = 6.0f;
            style.ChildRounding     = 6.0f;
            style.FrameRounding     = 5.0f;
            style.PopupRounding     = 6.0f;
            style.ScrollbarRounding = 6.0f;
            style.GrabRounding      = 5.0f;
            style.TabRounding       = 6.0f;

            style.WindowPadding     = ImVec2(10, 10);
            style.FramePadding      = ImVec2(6, 4);
            style.ItemSpacing       = ImVec2(8, 6);
            style.ItemInnerSpacing  = ImVec2(6, 4);
            style.IndentSpacing     = 20.0f;
            style.ScrollbarSize     = 14.0f;

            // --- Texte ---
            colors[ImGuiCol_Text]                  = ImVec4(0.95f, 0.96f, 0.98f, 1.00f);
            colors[ImGuiCol_TextDisabled]          = ImVec4(0.55f, 0.58f, 0.60f, 1.00f);

            // --- Backgrounds ---
            colors[ImGuiCol_WindowBg]              = ImVec4(0.12f, 0.13f, 0.15f, 1.00f);
            colors[ImGuiCol_ChildBg]               = ImVec4(0.14f, 0.15f, 0.17f, 1.00f);
            colors[ImGuiCol_PopupBg]               = ImVec4(0.10f, 0.11f, 0.13f, 0.98f);

            // --- Bordures ---
            colors[ImGuiCol_Border]                = ImVec4(0.20f, 0.22f, 0.25f, 1.00f);
            colors[ImGuiCol_BorderShadow]          = ImVec4(0, 0, 0, 0);

            // --- Frames (inputs, boutons) ---
            colors[ImGuiCol_FrameBg]               = ImVec4(0.18f, 0.19f, 0.22f, 1.00f);
            colors[ImGuiCol_FrameBgHovered]        = ImVec4(0.85f, 0.20f, 0.20f, 0.40f);
            colors[ImGuiCol_FrameBgActive]         = ImVec4(0.90f, 0.15f, 0.15f, 0.65f);

            // --- Titres ---
            colors[ImGuiCol_TitleBg]               = ImVec4(0.10f, 0.11f, 0.13f, 1.00f);
            colors[ImGuiCol_TitleBgActive]         = ImVec4(0.85f, 0.15f, 0.15f, 1.00f);
            colors[ImGuiCol_TitleBgCollapsed]      = ImVec4(0.10f, 0.11f, 0.13f, 0.75f);

            // --- Boutons ---
            colors[ImGuiCol_Button]                = ImVec4(0.85f, 0.15f, 0.15f, 0.85f);
            colors[ImGuiCol_ButtonHovered]         = ImVec4(0.95f, 0.20f, 0.20f, 1.00f);
            colors[ImGuiCol_ButtonActive]          = ImVec4(0.70f, 0.10f, 0.10f, 1.00f);

            // --- Headers (TreeNode, Selectable) ---
            colors[ImGuiCol_Header]                = ImVec4(0.85f, 0.15f, 0.15f, 0.55f);
            colors[ImGuiCol_HeaderHovered]         = ImVec4(0.95f, 0.20f, 0.20f, 0.75f);
            colors[ImGuiCol_HeaderActive]          = ImVec4(0.85f, 0.15f, 0.15f, 1.00f);

            // --- Tabs ---
            colors[ImGuiCol_Tab]                   = ImVec4(0.15f, 0.16f, 0.18f, 1.00f);
            colors[ImGuiCol_TabHovered]            = ImVec4(0.90f, 0.20f, 0.20f, 0.80f);
            colors[ImGuiCol_TabActive]             = ImVec4(0.85f, 0.15f, 0.15f, 1.00f);
            colors[ImGuiCol_TabUnfocused]          = ImVec4(0.15f, 0.16f, 0.18f, 1.00f);
            colors[ImGuiCol_TabUnfocusedActive]    = ImVec4(0.25f, 0.26f, 0.28f, 1.00f);

            // --- Scrollbar ---
            colors[ImGuiCol_ScrollbarBg]           = ImVec4(0.12f, 0.13f, 0.15f, 1.00f);
            colors[ImGuiCol_ScrollbarGrab]         = ImVec4(0.40f, 0.42f, 0.45f, 1.00f);
            colors[ImGuiCol_ScrollbarGrabHovered]  = ImVec4(0.85f, 0.15f, 0.15f, 0.80f);
            colors[ImGuiCol_ScrollbarGrabActive]   = ImVec4(0.90f, 0.20f, 0.20f, 1.00f);

            // --- Check / Slider ---
            colors[ImGuiCol_CheckMark]             = ImVec4(0.95f, 0.20f, 0.20f, 1.00f);
            colors[ImGuiCol_SliderGrab]            = ImVec4(0.85f, 0.15f, 0.15f, 1.00f);
            colors[ImGuiCol_SliderGrabActive]      = ImVec4(0.95f, 0.20f, 0.20f, 1.00f);

            // --- Docking ---
            colors[ImGuiCol_DockingPreview]        = ImVec4(0.95f, 0.20f, 0.20f, 0.70f);
            colors[ImGuiCol_DockingEmptyBg]        = ImVec4(0.10f, 0.11f, 0.13f, 1.00f);

            // --- Sélections ---
            colors[ImGuiCol_TextSelectedBg]        = ImVec4(0.85f, 0.15f, 0.15f, 0.50f);

            // --- Plots ---
            colors[ImGuiCol_PlotLines]             = ImVec4(0.95f, 0.20f, 0.20f, 1.00f);
            colors[ImGuiCol_PlotHistogram]         = ImVec4(0.85f, 0.15f, 0.15f, 1.00f);

            // === CONFIG ===
            io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
            io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
            io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
        }
    }
    
    void EditorApplication::handleEvents(const std::optional<sf::Event>& event)
    {
        ImGui::SFML::ProcessEvent(m_window, *event);
        m_panelManager->handleEvents(event);

        if (event->is<sf::Event::Closed>())
            m_window.close();
    }

    void EditorApplication::update()
    {
        ImGui::SFML::Update(m_window, sf::seconds(m_timer.deltaTime()));

        m_panelManager->update();
    }

    void EditorApplication::render()
    {
        ImGui::SFML::Render(m_window);
    }
}