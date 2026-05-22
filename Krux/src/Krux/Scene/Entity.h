#pragma once
#include <ECS/Entity.h>

#include "Krux/Core/UUID.h"

namespace Krux {
    class Scene;

    class Entity {
    public:
        Entity();
        Entity(ecs::entity handle, Scene* scene);
        Entity(const Entity& other);
        
        void AddChild(Entity& e);
        void BecomeOrphan();
        const std::vector<UUID64>& GetChildEntities() const& { return m_ChildEntities; }
        bool IsRoot() const { return !m_IsChild; }

        template<typename C, typename... Args>
        C* AddComponent(Args&&... args); 

        template<typename C>
        C* GetComponent() const;

        operator ecs::entity() const { return m_EntityHandle; }


    private:
        ecs::entity m_EntityHandle{ ecs::entity::invalid_entity };
        Scene* m_Scene;

        // Relations
        bool m_IsChild = false;
        Entity* m_Parent = nullptr;
        std::vector<UUID64> m_ChildEntities;
    };
}

#include "Entity.inl"