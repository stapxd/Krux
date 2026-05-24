#include "krxpch.h"
#include "Entity.h"

#include "Components.h"

#include <algorithm>

namespace Krux {
	Entity::Entity()
		: m_Scene(nullptr)
	{
	}

	Entity::Entity(ecs::entity handle, Scene* scene)
		: m_EntityHandle(handle), m_Scene(scene)
	{
	}

	Entity::Entity(const Entity& other)
		: m_EntityHandle(other.m_EntityHandle), m_Scene(other.m_Scene)
	{
	}

	void Entity::AddChild(Entity& e) {
		IDComponent* idComp = m_Scene->GetComponent<IDComponent>(e);
		AddChild(idComp->ID);
	}

	void Entity::AddChild(const UUID64& id)
	{
		Entity& e = m_Scene->m_Entities[id];

		Entity* parent = e.m_Parent;
		if (e.m_IsChild && parent) {
			auto it = std::find(parent->m_ChildEntities.begin(), parent->m_ChildEntities.end(), id);
			if (it != parent->m_ChildEntities.end())
				parent->m_ChildEntities.erase(it);
		}

		m_ChildEntities.emplace_back(id);

		e.m_Parent = this;
		e.m_IsChild = true;
	}

	void Entity::BecomeOrphan()
	{
		if (!m_Parent && !m_IsChild)
			return;

		IDComponent* idComp = m_Scene->GetComponent<IDComponent>(*this);

		Entity* parent = m_Parent;
		if (m_IsChild && parent) {
			auto it = std::find(parent->m_ChildEntities.begin(), parent->m_ChildEntities.end(), idComp->ID);
			if (it != parent->m_ChildEntities.end())
				parent->m_ChildEntities.erase(it);

			m_Parent = nullptr;
			m_IsChild = false;
		}

	}

}