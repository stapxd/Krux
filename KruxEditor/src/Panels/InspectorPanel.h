#pragma once

#include "Krux/Scene/Scene.h"

#include "Krux/Core/UUID.h"

namespace Krux {

	class InspectorPanel {
	public:
		InspectorPanel(Scene* scene);
		void OnRender(UUID64 selectedEntityID);

		template<typename Component>
		void DrawComponent(Entity* e, void(*callback)(Component*)) {
			if (m_Scene->Has<Component>(*e)) {
				if (ImGui::CollapsingHeader(Component::GetName(), ImGuiTreeNodeFlags_None)) {
					Component* comp = m_Scene->GetComponent<Component>(*e);
					callback(comp);
				}
			}
		}

		bool IsFocused() const { return m_IsFocused; }
		bool* Open() { return &m_IsOpen; }

	private:
		bool m_IsOpen = true;
		bool m_IsFocused = false;

		Scene* m_Scene;
		UUID64 m_SelectedId = UUID64::INVALID;
	};

}