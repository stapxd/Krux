#include "krxpch.h"
#include "Scene.h"

#include "Components.h"

#include "Krux/Render/Renderer.h"
#include "Krux/Render/Renderer2D.h"

namespace Krux {
	
	Scene::Scene()
	{
	}

	UUID64 Scene::CreateEntity()
	{
		ecs::entity e = m_Registry.create();
		Entity entity(e, this);
		UUID64 id;

		AddComponent<IDComponent>(entity, id);
		AddComponent<TagComponent>(entity);
		AddComponent<NameComponent>(entity);
		AddComponent<TransformComponent>(entity);

		m_Entities[id] = entity;

		return id;
	}

	UUID64 Scene::CreateNewFromExisting(UUID64 id) {
		Entity* fromEnt = FindByUUID(id);
		if (!fromEnt) {
			return UUID64::INVALID;
		}

		std::vector<UUID64> childrenSnapshot = fromEnt->GetChildEntities();

		ecs::entity e = m_Registry.create();
		Entity entity(e, this);
		UUID64 newId;

		AddComponent<IDComponent>(entity, newId);
		m_Entities[newId] = entity;

		CopyAllComponents(id, newId);

		for (UUID64 childId : childrenSnapshot) {
			UUID64 newChildId = CreateNewFromExisting(childId);
			if (newChildId != UUID64::INVALID) {
				m_Entities[newId].AddChild(newChildId);
			}
		}
		
		return newId;
	}

	void Scene::CopyAllComponents(UUID64 from, UUID64 to) {
		Entity* fromEntPtr = FindByUUID(from);
		Entity* toEntPtr = FindByUUID(to);

		std::apply([&](const auto&&... args) {

			auto copyComponentFunc = [&](const auto& comp) {
				using T = std::decay_t<decltype(comp)>;

				if (fromEntPtr->HasComponent<T>() && typeid(T) != typeid(IDComponent)) {
					T* newComp = AddComponent<T>(*toEntPtr);
					*newComp = *(fromEntPtr->GetComponent<T>());
				}
			};

			(copyComponentFunc(args), ...);

		}, AllComponents{});
	}

	void Scene::DeleteEntity(const Entity& e)
	{
		std::vector<UUID64> entitiesToDelete;
		CollectAllChildren(e, entitiesToDelete);

		entitiesToDelete.push_back(e.GetComponent<IDComponent>()->ID);

		for (auto uuid : entitiesToDelete) {
			Entity* target = FindByUUID(uuid);
			if (target) {
				m_Registry.destroy(*target);
				m_Entities.erase(uuid);
			}
		}
	}

	void Scene::CollectAllChildren(const Entity& parent, std::vector<UUID64>& outList) {
		for (auto childUUID : parent.GetChildEntities()) {
			Entity* child = FindByUUID(childUUID);
			if (child) {
				CollectAllChildren(*child, outList);
				outList.push_back(childUUID);
			}
		}
	}

	Entity* Scene::FindByUUID(UUID64 id)
	{
		auto it = m_Entities.find(id);
		if (it != m_Entities.end())
			return &it->second;

		return nullptr;
	}

	UUID64 Scene::GetUUIDFromECS(ecs::entity entity) {
		if(entity.IsValid())
			return m_Registry.get<IDComponent>(entity)->ID;

		return UUID64::INVALID;
	}

	void Scene::UpdateWorldPositions()
	{
		for (auto& entityPair : m_Entities) {
			if (entityPair.second.IsRoot())
				UpdateWorldPositionRecursively(entityPair.second);
		}
	}

	void Scene::UpdateWorldPositionRecursively(Entity& e, glm::vec3 parentPosition /*= glm::vec3(0.0f)*/)
	{
		TransformComponent* trm = e.GetComponent<TransformComponent>();

		trm->WorldPosition = trm->LocalPosition + parentPosition;

		for (UUID64 childUUID : e.GetChildEntities()) {
			Entity* child = FindByUUID(childUUID);
			if (child) {
				UpdateWorldPositionRecursively(*child, trm->WorldPosition);
			}
		}
	}

	void Scene::UpdateViewport(float width, float height)
	{
		if (width <= 0.0f || height <= 0.0f)
			return;

		m_ViewportSize.x = (float)width;
		m_ViewportSize.y = (float)height;

		auto group = m_Registry.group<CameraComponent>();
		for (auto& [e, cmr] : group) {
			cmr.Width  = width;
			cmr.Height = height;
			CameraSystem::RecalculateProjection(cmr);
		}
	}

	void Scene::OnUpdateEdit(Time time, const Camera& camera)
	{
		UpdateWorldPositions();

		Renderer2D::BeginFrame(camera);

			Renderer2D::BeginBatch();
			{
				auto group = m_Registry.group<TransformComponent, SpriteRendererComponent>();
				for (auto& [e, trm, sprR] : group) {
					Renderer2D::DrawSprite(trm, sprR, (int)e.GetID());
				}
			}

			{
				auto group = m_Registry.group<TransformComponent, CircleRendererComponent>();
				for (auto& [e, trm, circleR] : group) {
					Renderer2D::DrawCircle(trm.WorldPosition, circleR.Radius, circleR.Color, circleR.Thickness, circleR.Fade, (int)e.GetID());
				}
			}
			Renderer2D::EndBatch();

		Renderer2D::EndFrame();
	}

	void Scene::OnUpdateRuntime(Time time)
	{
		UpdateWorldPositions();

		CameraComponent* primaryCamera = nullptr;
		glm::mat4 primaryCameraTransform = glm::mat4(1.0f);
		{
			auto group = m_Registry.group<TransformComponent, CameraComponent>();
			for (auto& [e, trm, cmr] : group) {
				if (cmr.Primary) {
					primaryCamera = &cmr;
					primaryCameraTransform = trm.GetTransform();
					break;
				}
			}
		}

		if (primaryCamera) {
			Renderer2D::BeginFrame(*primaryCamera, primaryCameraTransform);

				Renderer2D::BeginBatch();
					{
						auto group = m_Registry.group<TransformComponent, SpriteRendererComponent>();
						for (auto& [e, trm, sprR] : group) {
							Renderer2D::DrawSprite(trm, sprR, (int)e.GetID());
						}
					}

					{
						auto group = m_Registry.group<TransformComponent, CircleRendererComponent>();
						for (auto& [e, trm, circleR] : group) {
							Renderer2D::DrawCircle(trm.WorldPosition, circleR.Radius, circleR.Color, circleR.Thickness, circleR.Fade, (int)e.GetID());
						}
					}
				Renderer2D::EndBatch();

			Renderer2D::EndFrame();
		}
	}

}