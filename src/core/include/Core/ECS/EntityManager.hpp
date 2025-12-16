#ifndef _CORE_ENTITY_MANAGER_HPP__
#define _CORE_ENTITY_MANAGER_HPP__

#include <entt/entt.hpp>

namespace Core
{
    class EntityManager
    {
    public:
        EntityManager() = default;
        ~EntityManager() = default;

        entt::entity& createEntity();

        void destroyEntity(entt::entity entity);

        void clear();

        entt::registry& getRegistry() { return m_registry; }
        const entt::registry& getRegistry() const { return m_registry; }

    private:
        entt::registry m_registry;

    };
}

#endif