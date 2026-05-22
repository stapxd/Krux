#pragma once

#include "Krux/Core/Log.h"
#include "Krux/Core/Time.h"
#include "Krux/Core/UUID.h"

#include "Krux/Render/OrthographicCamera.h"

#include <ECS/Registry.h>

namespace Krux {
    class Entity; 

    enum class SceneState { Edit, Play };

    class Scene {
    public:
        Scene();

        SceneState GetState() { return m_State; }

        Entity& CreateEntity();
        void DeleteEntity(const Entity& e);

        const std::unordered_map<UUID64, Entity>& GetEntities() const& { return m_Entities; }
        Entity* FindByUUID(UUID64 id);

        template<typename C, typename... Args>
        C* AddComponent(const Entity& e, Args&&... args);

        template<typename C>
        C* GetComponent(const Entity& e);

        template<typename C>
        bool Has(Entity e);

        void OnUpdateEdit(Time time, const OrthographicCamera& camera);
        void OnUpdateRuntime(Time time);

        template<typename... C>
        auto GetAllWith();

    private:
        SceneState m_State = SceneState::Edit;
        ecs::registry m_Registry;

        // add positions so they are correctly sorted in SceneHierarchy
        std::unordered_map<UUID64, Entity> m_Entities;
    };
}

#include "Scene.inl"