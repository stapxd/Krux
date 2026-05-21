#pragma once
#include <ECS/Entity.h>

namespace Krux {
    class Scene;

    class Entity {
    public:
        Entity(ecs::entity handle, Scene* scene);
        Entity(const Entity& other);

        template<typename C, typename... Args>
        C* AddComponent(Args&&... args); 

        template<typename C>
        C* GetComponent();

        operator ecs::entity() const { return m_EntityHandle; }

    private:
        ecs::entity m_EntityHandle{ ecs::entity::invalid_entity };
        Scene* m_Scene;
    };
}

#include "Entity.inl"