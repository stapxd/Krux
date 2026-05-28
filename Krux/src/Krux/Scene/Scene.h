#pragma once

#include "Krux/Core/Log.h"
#include "Krux/Core/Time.h"
#include "Krux/Core/UUID.h"

#include "Krux/Render/Cameras/Camera.h"

#include <ECS/Registry.h>

namespace Krux {
    class Entity; 

    enum class SceneState { Edit, Play };

    class Scene {
    public:
        Scene();

        SceneState GetState() { return m_State; }

        UUID64 CreateEntity();
        UUID64 CreateNewFromExisting(UUID64 id);
        void CopyAllComponents(UUID64 from, UUID64 to);
        void DeleteEntity(const Entity& e);

        const std::unordered_map<UUID64, Entity>& GetEntities() const& { return m_Entities; }
        Entity* FindByUUID(UUID64 id);

        template<typename C, typename... Args>
        C* AddComponent(const Entity& e, Args&&... args);

        template<typename C>
        C* GetComponent(UUID64 id);

        template<typename C>
        C* GetComponent(const Entity& e);

        template<typename C>
        void RemoveComponent(const Entity& e);

        template<typename C>
        bool Has(Entity e);

        void UpdateWorldPositions();
        void UpdateWorldPositionRecursively(Entity& e, glm::vec3 parentPosition = glm::vec3(0.0f));

        void OnUpdateEdit(Time time, const Camera& camera);
        void OnUpdateRuntime(Time time);

        template<typename... C>
        auto GetAllWith();

        void SetSelectedEntityID(UUID64 id) { m_SelectedEntityID = id; }
        UUID64 GetSelectedEntityID() { return m_SelectedEntityID; }

    private:
        void CollectAllChildren(const Entity& parent, std::vector<UUID64>& outList);

    private:
        SceneState m_State = SceneState::Edit;
        ecs::registry m_Registry;

        // add positions so they are correctly sorted in SceneHierarchy
        std::unordered_map<UUID64, Entity> m_Entities;
        UUID64 m_SelectedEntityID = UUID64::INVALID;

        friend Entity;
    };
}

#include "Scene.inl"