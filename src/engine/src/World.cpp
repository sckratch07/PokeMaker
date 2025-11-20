#include "Engine/World.hpp"

/**
 * @file World.cpp
 * @brief Implémentation de la classe World.
 */

namespace Engine
{
    World::World()
    {
        
    }

    entt::entity World::createEntity()
    {
        return m_registry.create();
    }

    void World::destroyEntity(entt::entity entity)
    {
        if (m_registry.valid(entity))
            m_registry.destroy(entity);
    }

    void World::addSystem(std::unique_ptr<System> system)
    {
        m_systems.push_back(std::move(system));
    }

    void World::update(float dt)
    {
        // On met à jour tous les systèmes dans l'ordre d'ajout
        for (auto& system : m_systems)
        {
            system->update(m_registry, dt);
        }
    }

    entt::registry& World::getRegistry()
    {
        return m_registry;
    }
}
