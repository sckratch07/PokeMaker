#ifndef _MAPEDITOR_MAPEDITOR_HPP__
#define _MAPEDITOR_MAPEDITOR_HPP__

#include <memory>

#include "Core/State.hpp"
#include "Core/EntityManager.hpp"
#include "Core/EventManager.hpp"
#include "Core/Timer.hpp"

namespace MapEditor
{
    class EditorContext;
    class EditorUI;

    /**
    * @brief State principal de l'éditeur de map.
    *
    * MapEditor est un State du moteur responsable de :
    * - la gestion de l'édition de maps
    * - l'affichage de l'UI ImGui (docking)
    * - la coordination des outils (brush, sélection, caméra)
    * - la gestion des entités d'éditeur (NPC, Player)
    *
    * Ce State n'implémente aucune logique métier lourde,
    * il orchestre les sous-systèmes spécialisés.
    */
    class MapEditor : public Core::State
    {
    public:
        /**
        * @brief Constructeur
        */
        MapEditor();

        /**
        * @brief Destructeur
        */
        ~MapEditor() override;

        /**
        * @brief Appelé à l'entrée dans l'état
        */
        void onEnter() override;

        /**
        * @brief Appelé à la sortie de l'état
        */
        void onExit() override;

        /**
        * @brief Mise à jour logique
        *
        * @param dt Delta time en secondes
        */
        void update(float dt) override;

        /**
        * @brief Rendu graphique
        */
        void render(sf::RenderWindow& window) override;

    private:
        /**
        * @brief Initialisation interne de l'éditeur
        */
        void initialize();

        /**
        * @brief Mise à jour des systèmes d'édition
        */
        void updateSystems(float dt);

        /**
        * @brief Rendu des systèmes de map
        */
        void renderSystems();

        std::unique_ptr<EditorContext> m_context; /**< Contexte global de l'éditeur */
        std::unique_ptr<EditorUI> m_ui; /**< Interface utilisateur ImGui */

        Core::EntityManager m_entities; /**< Entités d'éditeur */
        Core::EventManager m_events; /**< Événements d'éditeur */
        Core::Timer m_timer; /**< Timer interne */

        bool m_initialized = false;
    };
}

#endif // _MAPEDITOR_MAPEDITOR_HPP__