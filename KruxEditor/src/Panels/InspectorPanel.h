#pragma once

#include "Panel.h"

#include "Krux/Scene/Scene.h"
#include "Krux/Core/UUID.h"

#include <imgui.h>

namespace Krux {

	class InspectorPanel : public Panel {
	public:
		InspectorPanel(Scene* scene);
		
		bool DrawDragFloat3(const char* label, float v[3], const char* colNames[3], float defaultVal = 0.0f, float v_speed = 1.0f, float v_min = 0.0f, float v_max = 0.0f,
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
		void DrawComponent(Entity* e, Func callback, bool deletable = false) {
			if (e->HasComponent<Component>()) {

				ImGui::PushID(typeid(Component).name());
				float button_size = 20.0f;
				float padding = ImGui::GetStyle().FramePadding.x;
				float available_width = ImGui::GetContentRegionAvail().x;

				bool opened = ImGui::CollapsingHeader(Component::GetName(),
					ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_AllowOverlap);

				if (deletable) {
					ImGui::SameLine(available_width - button_size + padding);

					ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.7f, 0.3f, 0.3f, 1.0f));
					ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.5f, 0.3f, 0.3f, 1.0f));
					ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.5f, 0.1f, 0.1f, 1.0f));

					if (ImGui::Button("X", ImVec2(button_size, button_size))) {
						e->RemoveComponent<Component>();
					}

					ImGui::PopStyleColor(3);
				}

				if (opened && e->HasComponent<Component>()) {
					Component* comp = e->GetComponent<Component>();
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