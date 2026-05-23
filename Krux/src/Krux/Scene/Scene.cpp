#include "krxpch.h"
#include "Scene.h"

#include "Components.h"

#include "Krux/Render/Renderer.h"
#include "Krux/Render/Renderer2D.h"

namespace Krux {
	
	Scene::Scene()
	{
	}

	Entity& Scene::CreateEntity()
	{
		ecs::entity e = m_Registry.create();
		Entity entity(e, this);
		UUID64 id;

		AddComponent<IDComponent>(entity, id);
		AddComponent<TagComponent>(entity);
		AddComponent<NameComponent>(entity);
		AddComponent<TransformComponent>(entity);

		m_Entities[id] = entity;

		return m_Entities[id];
	}

	void Scene::DeleteEntity(const Entity& e)
	{
		IDComponent* idComp = m_Registry.get<IDComponent>(e);
		m_Entities.erase(idComp->ID);
		m_Registry.destroy(e);
	}

	Entity* Scene::FindByUUID(UUID64 id)
	{
		auto it = m_Entities.find(id);
		if (it != m_Entities.end())
			return &it->second;

		return nullptr;
	}

	void Scene::OnUpdateEdit(Time time, const OrthographicCamera& camera)
	{
		Renderer::Clear();
		
		Renderer2D::BeginFrame(camera);

			Renderer2D::BeginBatch();
			{
				auto group = m_Registry.group<TransformComponent, SpriteRendererComponent>();
				for (auto& [e, trm, sprR] : group) {
					Renderer2D::DrawSprite(trm, sprR);
				}
			}

			{
				auto group = m_Registry.group<TransformComponent, CircleRendererComponent>();
				for (auto& [e, trm, circleR] : group) {
					Renderer2D::DrawCircle(trm.Position, circleR.Radius, circleR.Color, circleR.Thickness, circleR.Fade);
				}
			}
			Renderer2D::EndBatch();

		Renderer2D::EndFrame();
	}

	void Scene::OnUpdateRuntime(Time time)
	{

	}

}