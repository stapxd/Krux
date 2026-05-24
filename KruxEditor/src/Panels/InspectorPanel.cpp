#include "InspectorPanel.h"

#include "Krux/Scene/Components.h"

#include <imgui.h>

namespace Krux {

	InspectorPanel::InspectorPanel(Scene* scene)
		: m_Scene(scene)
	{
	}

	// TODO: add ability to add & delete components 
	void InspectorPanel::OnRender(UUID64 selectedEntityID)
	{
		if (m_IsOpen) {
			Entity* e = m_Scene->FindByUUID(selectedEntityID);

			ImGui::Begin("Inspector", &m_IsOpen);

			if (e && selectedEntityID.IsValid()) {
				// TODO: add tag component

				// Name Component
				DrawComponent<NameComponent>(e, [](NameComponent* comp) {
					char buffer[256];
					memset(buffer, 0, sizeof(buffer));
					strncpy_s(buffer, sizeof(buffer), comp->Text.c_str(), sizeof(buffer));

					if (ImGui::InputText("##Name", buffer, IM_ARRAYSIZE(buffer))) {
						comp->Text = std::string(buffer);
					}
				});

				// TODO: parent entity must affect its children
				// Transform Component
				DrawComponent<TransformComponent>(e, [](TransformComponent* comp) {
					ImGui::DragFloat3("Position", &comp->LocalPosition[0], 0.02f);
					ImGui::DragFloat3("Rotation", &comp->Rotation[0], 0.02f);
					ImGui::DragFloat3("Scale",	  &comp->Scale[0]   , 0.02f);
				});

				// TODO: add ability to add Textures
				// Sprite Renderer Component
				DrawComponent<SpriteRendererComponent>(e, [](SpriteRendererComponent* comp) {
					ImGui::ColorEdit4("Color", &comp->Color[0]);
					ImGui::DragFloat("Tiling Factor", &comp->TilingFactor, 1.0f, 1.0f, 50.0f);
				});

				// Circle Renderer Component
				DrawComponent<CircleRendererComponent>(e, [](CircleRendererComponent* comp) {
					ImGui::ColorEdit4("Color", &comp->Color[0]);
					ImGui::DragFloat("Radius", &comp->Radius, 0.02f, 0.0f);
					ImGui::DragFloat("Thickness", &comp->Thickness, 0.01f, 0.01f, 1.0f);
					ImGui::DragFloat("Fade", &comp->Fade, 0.02f, 0.02f, 1.0f);
				});
			}

			ImGui::End();
		}
	}

}