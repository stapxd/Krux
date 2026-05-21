#include "krxpch.h"
#include "Scene.h"

#include "Components.h"

#include "Krux/Render/Renderer.h"
#include "Krux/Render/Renderer2D.h"

namespace Krux {
	
	Scene::Scene()
	{
	}

	Entity Scene::CreateEntity()
	{
		ecs::entity e = m_Registry.create();
		Entity entity(e, this);

		AddComponent<Components::IDComponent>(entity, UUID64());
		AddComponent<Components::Tag>(entity);
		AddComponent<Components::Transform>(entity);

		return entity;
	}

	void Scene::OnUpdateEdit(Time time, const OrthographicCamera& camera)
	{
		Renderer::Clear();
		
		Renderer2D::BeginFrame(camera);

		{
			auto group = m_Registry.group<Components::Transform, Components::SpriteRenderer>();

			Renderer2D::BeginBatch();

			for (auto& [e, trm, sprR] : group) {
				Renderer2D::DrawSprite(trm, sprR);
			}

			Renderer2D::EndBatch();
		}

		Renderer2D::EndFrame();
	}

	void Scene::OnUpdateRuntime(Time time)
	{

	}

}