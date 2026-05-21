#include "krxpch.h"
#include "Entity.h"

namespace Krux {
	
	Entity::Entity(ecs::entity handle, Scene* scene)
		: m_EntityHandle(handle), m_Scene(scene)
	{
	}

	Entity::Entity(const Entity& other)
		: m_EntityHandle(other.m_EntityHandle), m_Scene(other.m_Scene)
	{
	}

}