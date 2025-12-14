#include "Core/EntityManager.hpp"

namespace Core
{
    entt::entity EntityManager::createEntity()
    {
        return m_registry.create();
    }

    void EntityManager::destroyEntity(entt::entity entity)
    {
        if (m_registry.valid(entity))
            m_registry.destroy(entity);
    }

    void EntityManager::clear()
    {
        m_registry.clear();
    }

    entt::registry& EntityManager::registry()
    {
        return m_registry;
    }

    const entt::registry& EntityManager::registry() const
    {
        return m_registry;
    }
}