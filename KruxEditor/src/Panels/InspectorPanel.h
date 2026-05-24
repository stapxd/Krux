#pragma once

#include "Panel.h"

#include "Krux/Scene/Scene.h"
#include "Krux/Core/UUID.h"

namespace Krux {

	class InspectorPanel : public Panel {
	public:
		InspectorPanel(Scene* scene);
		
		virtual void RenderContent(PanelData panelData = std::monostate{}) override;

		template<typename Component>
		void DrawComponent(Entity* e, void(*callback)(Component*)) {
			if (m_Scene->Has<Component>(*e)) {
				if (ImGui::CollapsingHeader(Component::GetName(), ImGuiTreeNodeFlags_None)) {
					Component* comp = m_Scene->GetComponent<Component>(*e);
					callback(comp);
				}
			}
		}

	private:
		Scene* m_Scene;
		UUID64 m_SelectedId = UUID64::INVALID;
	};

}