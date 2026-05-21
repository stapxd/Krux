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

        Entity CreateEntity();

        template<typename C, typename... Args>
        C* AddComponent(Entity e, Args&&... args);

        template<typename C>
        C* GetComponent(Entity e);

        template<typename C>
        bool Has(Entity e);

        void OnUpdateEdit(Time time, const OrthographicCamera& camera);
        void OnUpdateRuntime(Time time);

        template<typename... C>
        auto GetAllWith();

    private:
        SceneState m_State = SceneState::Edit;
        ecs::registry m_Registry;
    };
}

#include "Scene.inl"