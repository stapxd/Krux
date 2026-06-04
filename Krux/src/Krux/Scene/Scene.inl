#pragma once
#include "Entity.h"

#include "Systems/CameraSystem.h"

#include <type_traits>

namespace Krux {
    template<typename C, typename... Args>
    C* Scene::AddComponent(const Entity& e, Args&&... args) {
        if (m_Registry.has<C>(e)) {
            return m_Registry.get<C>(e);
        }
        m_Registry.emplace<C>(e, std::forward<Args>(args)...);

        C* comp = m_Registry.get<C>(e);
        OnComponentAdded<C>(comp);
        return comp;
    }

    template<typename C>
    void Scene::OnComponentAdded(C* comp) {

        if constexpr (std::is_same_v<C, CameraComponent>) {
            comp->Width  = m_ViewportSize.x;
            comp->Height = m_ViewportSize.y;
            CameraSystem::RecalculateProjection(*comp);
        }

    }

    template<typename C>
    C* Scene::GetComponent(const Entity& e) {
        return m_Registry.get<C>(e);
    }

    template<typename C>
    C* Scene::GetComponent(UUID64 id) {
        if (!id.IsValid())
            return nullptr;

        Entity* e = FindByUUID(id);
        if (!e)
            return nullptr;

        return m_Registry.get<C>(*e);
    }

    template<typename C>
    bool Scene::Has(Entity e) {
        return m_Registry.has<C>(e);
    }

    template<typename... C>
    auto Scene::GetAllWith() {
        return m_Registry.group<C...>();
    }

    template<typename C>
    void Scene::RemoveComponent(const Entity& e) {
        m_Registry.remove<C>(e);
    }
}