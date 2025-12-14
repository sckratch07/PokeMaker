#include "MapEditor/MapEditor.hpp"
#include "MapEditor/EditorContext.hpp"
#include "MapEditor/UI/EditorUI.hpp"

#include "Core/Logger.hpp"

namespace MapEditor
{
    MapEditor::MapEditor() = default;

    MapEditor::~MapEditor() = default;

    void MapEditor::onEnter()
    {
        PM_LOG_INFO("Entering MapEditor state");
        initialize();
    }

    void MapEditor::onExit()
    {
        PM_LOG_INFO("Exiting MapEditor state");
        m_ui.reset();
        m_context.reset();
    }

    void MapEditor::initialize()
    {
        if (m_initialized)
            return;

        m_context = std::make_unique<EditorContext>();
        m_ui = std::make_unique<EditorUI>(*m_context, m_entities, m_events);

        m_timer.reset();
        m_initialized = true;

        PM_LOG_INFO("MapEditor initialized");
    }

    void MapEditor::update(float dt)
    {
        m_timer.tick();
        updateSystems(dt);
        if (m_ui)
            m_ui->update();
    }

    void MapEditor::render(sf::RenderWindow& window)
    {
        renderSystems();
        if (m_ui)
            m_ui->render();
    }

    void MapEditor::updateSystems(float dt)
    {
        (void)dt;
        // Mise à jour future :
        // - animation des tiles
        // - autotiles
        // - entités d'éditeur
    }

    void MapEditor::renderSystems()
    {
        // Rendu futur :
        // - map active
        // - layers visibles
        // - shaders
    }
}