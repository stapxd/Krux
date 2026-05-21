#include "krxpch.h"
#include "Scene.h"

#include "Components.h"

namespace Krux {
	
	Scene::Scene()
	{
	}

	Entity Scene::CreateEntity()
	{
		ecs::entity e = m_Registry.create();
		Entity entity(e, this);

		AddComponent<Components::ID>(entity, UUID());
		AddComponent<Components::Tag>(entity);
		AddComponent<Components::Transform>(entity);

		return entity;
	}

	void Scene::OnUpdateEdit(Time time)
	{

	}

	void Scene::OnUpdateRuntime(Time time)
	{

	}

}