#include "InspectorPanel.h"

#include "Krux/Utils/Utils.h"
#include "Krux/Scene/Components.h"

#include "Krux/Render/Assets/Texture2D.h"

#include <imgui.h>

namespace Krux {

	InspectorPanel::InspectorPanel(Scene* scene)
		: m_Scene(scene), Panel("Inspector")
	{
	}

	bool InspectorPanel::DrawDragFloat3(const char* label, float v[3], const char* colNames[3], float defaultVal, float v_speed, float v_min, float v_max,
		const char* format, ImGuiSliderFlags flags)
	{
		float availableHeight = ImGui::GetContentRegionAvail().y;
		float padding = 5.0f;

		ImGuiStyle* style = &ImGui::GetStyle();
		ImVec4* colors = style->Colors;

		bool active = false;
		if (ImGui::BeginTable(label, 4, ImGuiTableFlags_None))
		{
			ImGui::TableSetupColumn("Label", ImGuiTableColumnFlags_WidthFixed, 50.0f);
			ImGui::TableSetupColumn("X", ImGuiTableColumnFlags_WidthStretch);
			ImGui::TableSetupColumn("Y", ImGuiTableColumnFlags_WidthStretch);
			ImGui::TableSetupColumn("Z", ImGuiTableColumnFlags_WidthStretch);

			ImGui::TableNextRow();

			ImGui::TableSetColumnIndex(0);
			ImGui::Dummy(ImVec2(0.0f, 1.3f));
			ImGui::Text("%s", label);

			for (int i = 1; i <= 3; ++i) {
				ImGui::TableSetColumnIndex(i);

				ImGui::PushStyleColor(ImGuiCol_Button, ImGui::GetStyleColorVec4(ImGuiCol_WindowBg));
				ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.3f, 0.3f, 0.3f, 1.0f));
				ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.1f, 0.1f, 0.1f, 1.0f));
				ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(10.0f, 5.0f));

				if (ImGui::Button(colNames[i - 1])) {
					v[i - 1] = defaultVal;
					active = true;
				}

				ImGui::PopStyleColor(3);
				ImGui::PopStyleVar(1);

				ImGui::SameLine(); 

				ImGui::PushID(i);
				ImGui::SetNextItemWidth(-FLT_MIN);
				if (ImGui::DragFloat("##v", &v[i - 1], v_speed, v_min, v_max, format, flags)) {
					active = true;
				}
				ImGui::PopID();
			}

			ImGui::EndTable();
		}

		return active;
	}

	void InspectorPanel::RenderAddableComponents(Entity* e)
	{
		if (ImGui::BeginPopup("AddComponent")) {
			std::apply([e](auto... args) {
				(AddComponentHelper<std::decay_t<decltype(args)>>(e), ...);
			}, AllComponents{});

			ImGui::EndPopup();
		}
	}

	// TODO: add ability to add & delete components
	void InspectorPanel::RenderContent(PanelData panelData)
	{
		if(std::holds_alternative<UUID64>(panelData)) {
			UUID64 selectedEntityID = std::get<UUID64>(panelData);

			Entity* e = m_Scene->FindByUUID(selectedEntityID);

			if (e && selectedEntityID.IsValid()) {
				if (ImGui::Button("Add Component")) {
					ImGui::OpenPopup("AddComponent");
				}
				RenderAddableComponents(e);

				// TODO: add tag component

				// Name Component
				DrawComponent<NameComponent>(e, [](NameComponent* comp) {
					char buffer[256];
					memset(buffer, 0, sizeof(buffer));
					strncpy_s(buffer, sizeof(buffer), comp->Text.c_str(), sizeof(buffer));
					
					if (ImGui::BeginTable("Name", 2, ImGuiTableFlags_None))
					{
						ImGui::TableSetupColumn("Label", ImGuiTableColumnFlags_WidthFixed, 50.0f);
						ImGui::TableSetupColumn("Input", ImGuiTableColumnFlags_WidthStretch);

						ImGui::TableNextRow();

						ImGui::TableSetColumnIndex(0);
						ImGui::Dummy(ImVec2(0.0f, 0.7f));
						ImGui::Text("%s", "Name");

						ImGui::TableSetColumnIndex(1);
						ImGui::SetNextItemWidth(-FLT_MIN);

						if (ImGui::InputText("##Name", buffer, IM_ARRAYSIZE(buffer))) {
							comp->Text = std::string(buffer);
						}

						ImGui::EndTable();
					}
				});

				// Transform Component
				DrawComponent<TransformComponent>(e, [this](TransformComponent* comp) {
					const char* namings[3] = { "x", "y", "z" };
					ImGui::PushID("Pos");
					DrawDragFloat3("Position", &comp->LocalPosition[0], namings, 0.0f, 0.02f);
					ImGui::PopID();

					ImGui::PushID("Rot");
					glm::vec3 rotDegrees = glm::degrees(comp->Rotation);
					if (DrawDragFloat3("Rotation", &rotDegrees[0], namings, 0.0f, 0.02f)) {
						comp->Rotation = glm::radians(rotDegrees);
					}
					ImGui::PopID();

					ImGui::PushID("Scale");
					DrawDragFloat3("Scale",    &comp->Scale[0],  		namings, 1.0f, 0.02f);
					ImGui::PopID();
				});

				// TODO: add ability to add Textures
				// Sprite Renderer Component
				DrawComponent<SpriteRendererComponent>(e, [&](SpriteRendererComponent* comp) {
					ImGui::PushID("SpriteRendererComponent");
					ImGui::ColorEdit4("Color", &comp->Color[0]);
					ImGui::DragFloat("Tiling Factor", &comp->TilingFactor, 1.0f, 1.0f, 50.0f);

					float imageSize = 50.0f;
					if (comp->TextureHandle.IsValid()) {
						Ref<Texture2D> texture = AssetManager::GetAsset<Texture2D>(comp->TextureHandle);
						ImGui::ImageButton("EntityTexture", texture->GetRendererID(), ImVec2(imageSize, imageSize), ImVec2(0, 1), ImVec2(1, 0));
					}
					else {
						ImGui::Button("Texture", ImVec2(imageSize, imageSize));
					}

					if (ImGui::BeginDragDropTarget()) {
						if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("DND_FILE_PATH"))
						{
							std::filesystem::path path = std::string((const char*)payload->Data, payload->DataSize);
							comp->TextureHandle = AssetManager::Load<Texture2D>(path);
						}
						ImGui::EndDragDropTarget();
					}

					if (comp->TextureHandle.IsValid()) {
						ImGui::SameLine();
						Ref<Texture2D> texture = AssetManager::GetAsset<Texture2D>(comp->TextureHandle);
						bool isValidTexturePath = Utils::IsPathATexture(texture->GetPath());
						std::string pathStr = texture->GetPath().string();
						if (!isValidTexturePath) ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.8f, 0.2f, 0.2f, 1.0f));
						ImGui::Text("%s", pathStr.c_str());
						if (!isValidTexturePath) ImGui::PopStyleColor();

						ImGui::SameLine();
						if(ImGui::Button("X")) {
							comp->TextureHandle = AssetHandle();
						}
					}
					ImGui::PopID();

				}, true);

				// Circle Renderer Component
				DrawComponent<CircleRendererComponent>(e, [](CircleRendererComponent* comp) {
					ImGui::ColorEdit4("Color", &comp->Color[0]);
					ImGui::DragFloat("Radius", &comp->Radius, 0.02f, 0.0f);
					ImGui::DragFloat("Thickness", &comp->Thickness, 0.01f, 0.01f, 1.0f);
					ImGui::DragFloat("Fade", &comp->Fade, 0.02f, 0.02f, 1.0f);
				}, true);
			}
		}
	}

}
