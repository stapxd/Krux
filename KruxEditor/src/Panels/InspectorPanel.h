#pragma once

#include "Panel.h"

#include "Krux/Scene/Scene.h"
#include "Krux/Core/UUID.h"

#include <imgui.h>

namespace Krux {

	class InspectorPanel : public Panel {
	public:
		InspectorPanel(Scene* scene);
		
		void DrawDragFloat3(const char* label, float v[3], const char* colNames[3], float default = 0.0f, float v_speed = 1.0f, float v_min = 0.0f, float v_max = 0.0f,
			const char* format = "%.3f", ImGuiSliderFlags flags = 0);

		template<typename T>
		static void AddComponentHelper(Entity* e) {
			if (!e->HasComponent<T>()) {
				if (ImGui::MenuItem(T::GetName())) {
					e->AddComponent<T>();
				}
			}
		}

		void RenderAddableComponents(Entity* e);
		virtual void RenderContent(PanelData panelData = std::monostate{}) override;

		template<typename Component, typename Func>
		void DrawComponent(Entity* e, Func callback) {
			if (m_Scene->Has<Component>(*e)) {

				ImGui::PushID(typeid(Component).name());

				if (ImGui::CollapsingHeader(Component::GetName(), ImGuiTreeNodeFlags_None)) {
					Component* comp = m_Scene->GetComponent<Component>(*e);
					callback(comp);
				}

				ImGui::PopID();
			}
		}

	private:
		Scene* m_Scene;
		UUID64 m_SelectedId = UUID64::INVALID;
	};

}