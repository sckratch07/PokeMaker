#ifndef _CORE_ENTITY_MANAGER_HPP__
#define _CORE_ENTITY_MANAGER_HPP__

#include "Core/ECS/System/System.hpp"
#include <entt/entt.hpp>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

namespace Core
{
    class EntityManager
    {
    public:
        EntityManager() = default;
        ~EntityManager() = default;

        void serialize(const json& data);

        entt::entity createEntity();

        void addSystem(std::unique_ptr<System>& system);

        void destroyEntity(entt::entity entity);

        void update(float dt);

        void render(sf::RenderWindow& window);

        void clearEntities();
        
        void clearSystems();

        entt::registry& getRegistry() { return m_registry; }
        const entt::registry& getRegistry() const { return m_registry; }

    private:
        entt::registry m_registry;
        std::vector<std::unique_ptr<System>> m_systems;

    };
}

#endif