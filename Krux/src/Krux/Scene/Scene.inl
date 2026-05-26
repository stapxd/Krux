#pragma once
#include "Entity.h"

namespace Krux {
    template<typename C, typename... Args>
    C* Scene::AddComponent(const Entity& e, Args&&... args) {
        if (m_Registry.has<C>(e)) {
            return m_Registry.get<C>(e);
        }
        m_Registry.emplace<C>(e, std::forward<Args>(args)...);
        return m_Registry.get<C>(e);
    }

    template<typename C>
    C* Scene::GetComponent(const Entity& e) {
        return m_Registry.get<C>(e);
    }

    template<typename C>
    C* Scene::GetComponent(UUID64 id) {
        Entity* e = FindByUUID(id);
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