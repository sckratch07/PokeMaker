#include "Editor/EditorApplication.hpp"
#include "Editor/EditorUI.hpp"
#include "Editor/Tools/BrushTool.hpp"
#include "Editor/Tools/FillTool.hpp"
#include "Editor/Tools/SelectionTool.hpp"

#include <portable-file-dialogs.h>
#include <imgui.h>
#include <imgui-SFML.h>
#include <SFML/System/Clock.hpp>

namespace Editor {

EditorApplication::EditorApplication(const std::string& title, unsigned int width, unsigned int height)
    : m_window(std::make_unique<sf::RenderWindow>(sf::VideoMode(sf::Vector2u(width, height)), title))
    , m_running(true)
    , m_width(width)
    , m_height(height)
    , m_title(title)
    , m_pendingTool(EditorToolType::Selection)
    , m_autoSaveIntervalSeconds(300.0f) // sauvegarde automatique toutes les 5 minutes
    , m_closingRequested(false)
{
    // Initialisation ImGui-SFML
    if (ImGui::SFML::Init(*m_window))
    {
        ImGuiStyle& style = ImGui::GetStyle();
        ImGuiIO& io = ImGui::GetIO();
        ImVec4* colors = style.Colors;

        // === COULEURS PRINCIPALES ===
        colors[ImGuiCol_Text] = ImVec4(0.95f, 0.96f, 0.98f, 1.00f);
        colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.55f, 0.60f, 1.00f);
        colors[ImGuiCol_WindowBg] = ImVec4(0.10f, 0.12f, 0.15f, 1.00f);
        colors[ImGuiCol_ChildBg] = ImVec4(0.10f, 0.12f, 0.15f, 0.00f);
        colors[ImGuiCol_PopupBg] = ImVec4(0.12f, 0.14f, 0.18f, 0.95f);
        colors[ImGuiCol_Border] = ImVec4(0.25f, 0.30f, 0.45f, 0.50f);
        colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);

        colors[ImGuiCol_FrameBg] = ImVec4(0.20f, 0.25f, 0.35f, 1.00f);
        colors[ImGuiCol_FrameBgHovered] = ImVec4(0.25f, 0.35f, 0.50f, 1.00f);
        colors[ImGuiCol_FrameBgActive] = ImVec4(0.30f, 0.45f, 0.65f, 1.00f);

        colors[ImGuiCol_TitleBg] = ImVec4(0.12f, 0.15f, 0.20f, 1.00f);
        colors[ImGuiCol_TitleBgActive] = ImVec4(0.18f, 0.25f, 0.35f, 1.00f);
        colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.10f, 0.12f, 0.15f, 0.75f);

        colors[ImGuiCol_MenuBarBg] = ImVec4(0.13f, 0.16f, 0.22f, 1.00f);
        colors[ImGuiCol_ScrollbarBg] = ImVec4(0.10f, 0.12f, 0.15f, 1.00f);
        colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.25f, 0.35f, 0.50f, 1.00f);
        colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.30f, 0.45f, 0.65f, 1.00f);
        colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.35f, 0.50f, 0.75f, 1.00f);

        colors[ImGuiCol_CheckMark] = ImVec4(0.35f, 0.55f, 1.00f, 1.00f);
        colors[ImGuiCol_SliderGrab] = ImVec4(0.30f, 0.50f, 1.00f, 1.00f);
        colors[ImGuiCol_SliderGrabActive] = ImVec4(0.35f, 0.55f, 1.00f, 1.00f);

        colors[ImGuiCol_Button] = ImVec4(0.20f, 0.35f, 0.55f, 0.80f);
        colors[ImGuiCol_ButtonHovered] = ImVec4(0.30f, 0.50f, 0.85f, 1.00f);
        colors[ImGuiCol_ButtonActive] = ImVec4(0.20f, 0.40f, 0.75f, 1.00f);

        colors[ImGuiCol_Header] = ImVec4(0.20f, 0.35f, 0.55f, 0.80f);
        colors[ImGuiCol_HeaderHovered] = ImVec4(0.30f, 0.50f, 0.85f, 1.00f);
        colors[ImGuiCol_HeaderActive] = ImVec4(0.35f, 0.55f, 1.00f, 1.00f);

        colors[ImGuiCol_Separator] = ImVec4(0.28f, 0.35f, 0.50f, 0.60f);
        colors[ImGuiCol_SeparatorHovered] = ImVec4(0.35f, 0.55f, 0.90f, 1.00f);
        colors[ImGuiCol_SeparatorActive] = ImVec4(0.40f, 0.65f, 1.00f, 1.00f);

        colors[ImGuiCol_ResizeGrip] = ImVec4(0.26f, 0.46f, 0.98f, 0.25f);
        colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.26f, 0.46f, 0.98f, 0.70f);
        colors[ImGuiCol_ResizeGripActive] = ImVec4(0.26f, 0.46f, 0.98f, 0.95f);

        colors[ImGuiCol_Tab] = ImVec4(0.20f, 0.35f, 0.55f, 0.80f);
        colors[ImGuiCol_TabHovered] = ImVec4(0.30f, 0.50f, 0.85f, 1.00f);
        colors[ImGuiCol_TabActive] = ImVec4(0.35f, 0.55f, 1.00f, 1.00f);
        colors[ImGuiCol_TabUnfocused] = ImVec4(0.15f, 0.20f, 0.30f, 0.90f);
        colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.20f, 0.35f, 0.55f, 1.00f);

        colors[ImGuiCol_DockingPreview] = ImVec4(0.26f, 0.46f, 0.98f, 0.70f);
        colors[ImGuiCol_DockingEmptyBg] = ImVec4(0.15f, 0.18f, 0.22f, 1.00f);

        colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
        colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
        colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
        colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);

        colors[ImGuiCol_TextSelectedBg] = ImVec4(0.30f, 0.50f, 0.85f, 0.35f);
        colors[ImGuiCol_DragDropTarget] = ImVec4(0.26f, 0.46f, 0.98f, 0.95f);

        colors[ImGuiCol_NavHighlight] = ImVec4(0.26f, 0.46f, 0.98f, 1.00f);
        colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
        colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
        colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.10f, 0.10f, 0.10f, 0.60f);

        // === STYLE ===
        style.WindowRounding = 6.0f;
        style.FrameRounding = 4.0f;
        style.GrabRounding = 4.0f;
        style.ScrollbarRounding = 6.0f;
        style.TabRounding = 4.0f;
        style.WindowPadding = ImVec2(8.0f, 8.0f);
        style.FramePadding = ImVec2(5.0f, 3.0f);
        style.ItemSpacing = ImVec2(6.0f, 4.0f);
        style.IndentSpacing = 20.0f;
        style.ScrollbarSize = 16.0f;

        // === CONFIG ===
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
    }

    m_lastAutoSave = std::chrono::steady_clock::now();

    // crée l'outil par défaut (Selection)
    m_activeTool = std::make_unique<SelectionTool>();
}

EditorApplication::~EditorApplication()
{
    ImGui::SFML::Shutdown();
}

void EditorApplication::run()
{
    sf::Clock deltaClock;

    while (m_running && m_window->isOpen())
    {
        processEvents();

        float dt = deltaClock.restart().asSeconds();
        update(dt);

        ImGui::SFML::Update(*m_window, sf::seconds(dt));
        m_ui.render();

        // Vérifier si l’UI demande un changement d’outil
        //requestToolChange(m_ui.selectedTool());
        
        render();
    }
}

void EditorApplication::quit()
{
    // Tentative de fermeture : vérifier si projet modifié
    if (!confirmSaveBeforeQuit()) {
        // l'utilisateur a annulé la fermeture
        return;
    }

    m_running = false;
    if (m_window && m_window->isOpen())
        m_window->close();
}

sf::RenderWindow& EditorApplication::window()
{
    return *m_window;
}

void EditorApplication::processEvents()
{
    while (const std::optional<sf::Event>& event = m_window->pollEvent())
    {
        ImGui::SFML::ProcessEvent(*m_window, *event);

        if (event->is<sf::Event::Closed>())
        {
            m_closingRequested = true;
            quit();
            return;
        }
        else if(event->is<sf::Event::Closed>())
            handleShortcuts(*event);
    }
}

void EditorApplication::handleShortcuts(const sf::Event& event)
{
    const sf::Event::KeyPressed* keyPressed = event.getIf<sf::Event::KeyPressed>();
    if(!(keyPressed->control | keyPressed->system)) return; // system pour Mac Cmd

    if (keyPressed->code == sf::Keyboard::Key::N){
        // Nouveau projet
        // demander un nom via file dialog? Ici on ouvre un small input dialog:
        auto result = pfd::save_file("Nouveau projet - sauvegarder sous", "", {"JSON files", "*.json"}).result();
        if (!result.empty()) {
            // créer projet vide et sauver
            std::string name = "NouveauProjet";
            m_ui.projectManager().createProject(name);
            m_ui.projectManager().saveProjectAs(result);
            m_ui.projectManager().clearDirty();
        }
    } else if (keyPressed->code == sf::Keyboard::Key::O) {
        // Ouvrir
        auto result = pfd::open_file("Ouvrir un projet", "", {"JSON files", "*.json"}).result();
        if (!result.empty()) {
            std::string path = result.front();
            bool ok = m_ui.projectManager().loadProject(path);
            if (!ok) {
                pfd::message("Erreur", "Impossible d'ouvrir le projet (format ou chemin invalide)", pfd::choice::ok, pfd::icon::error);
            }
        }
    } else if (keyPressed->code == sf::Keyboard::Key::S) {
        // Sauvegarder
        if (m_ui.projectManager().activeProject) {
            if (m_ui.projectManager().currentFilePath.empty()) {
                auto result = pfd::save_file("Sauvegarder le projet sous", "", {"JSON files", "*.json"}).result();
                if (!result.empty()) {
                    bool ok = m_ui.projectManager().saveProjectAs(result);
                    if (ok) m_ui.projectManager().clearDirty();
                    else pfd::message("Erreur", "Impossible de sauvegarder le projet", pfd::choice::ok, pfd::icon::error);
                }
            } else {
                bool ok = m_ui.projectManager().saveProject();
                if (ok) m_ui.projectManager().clearDirty();
                else pfd::message("Erreur", "Impossible de sauvegarder le projet", pfd::choice::ok, pfd::icon::error);
            }
        }
    }
}

bool EditorApplication::confirmSaveBeforeQuit()
{
    // Si pas de projet actif ou pas modifié → ok
    if (!m_ui.projectManager().activeProject) return true;
    if (!m_ui.projectManager().dirty) return true;

    // On propose 3 options à l'utilisateur via dialog natif
    auto choice = pfd::message("Projet modifié", "Le projet contient des modifications non sauvegardées. Voulez-vous sauvegarder avant de quitter ?", 
                               pfd::choice::yes_no_cancel, pfd::icon::question).result();

    if (choice == pfd::button::ok) {
        // Yes (sauvegarder)
        if (m_ui.projectManager().currentFilePath.empty()) {
            auto res = pfd::save_file("Sauvegarder sous...", "", {"JSON files", "*.json"}).result();
            if (!res.empty()) {
                bool ok = m_ui.projectManager().saveProjectAs(res);
                if (ok) m_ui.projectManager().clearDirty();
                return ok;
            }
            return false;
        } else {
            bool ok = m_ui.projectManager().saveProject();
            if (ok) m_ui.projectManager().clearDirty();
            return ok;
        }
    } else if (choice == pfd::button::no) {
        // No -> quitter sans sauvegarder
        return true;
    } else {
        // Cancel -> ne pas fermer
        return false;
    }
}

void EditorApplication::update(float /*dt*/)
{
    // Changement d’outil demandé par l’UI ?
    if (!m_activeTool || m_activeTool->type() != m_pendingTool)
    {
        if (m_activeTool) 
            m_activeTool->end();

        switch (m_pendingTool)
        {
            case EditorToolType::Selection:
                m_activeTool = std::make_unique<Editor::SelectionTool>();
                break;
            case EditorToolType::Brush:
                m_activeTool = std::make_unique<BrushTool>(&m_ui.projectManager(), m_ui.m_tilePalette.get(), &m_ui.m_layerManager);
                break;
            case EditorToolType::Fill:
                m_activeTool = std::make_unique<Editor::FillTool>();
                break;
        }

        m_activeTool->begin();
    }

    // Mise à jour de l’outil actif
    if (m_activeTool)
        m_activeTool->update();
}

void EditorApplication::render()
{
    m_window->clear(sf::Color(45, 45, 48)); // couleur de fond neutre

    // Les appels ImGui sont déjà faits dans EditorUI::render()
    ImGui::SFML::Render(*m_window);

    m_window->display();
}

void EditorApplication::requestToolChange(EditorToolType type)
{
    m_pendingTool = type;
}


} // namespace Editor
