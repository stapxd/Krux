#include "SceneHierarchyPanel.h"

#include "Krux/Scene/Components.h"

#include <imgui.h>

namespace Krux {

	SceneHierarchyPanel::SceneHierarchyPanel(Scene* scene)
		: m_Scene(scene)
	{
	}

	// TODO: add drag&drop to make entities be children to other
	void SceneHierarchyPanel::OnRender()
	{
		if (m_IsOpen) {

			ImGui::Begin("Scene Hierarchy", &m_IsOpen);
			
			for (const auto& [id, e] : m_Scene->GetEntities()) {
				if (e.IsRoot())
					DrawEntityNode(id, e);
			}

			if (ImGui::IsWindowHovered() && ImGui::IsMouseClicked(ImGuiMouseButton_Left) && !ImGui::IsAnyItemHovered()) {
				m_SelectedEntityID = UUID64::INVALID;
			}

			if (ImGui::IsWindowHovered() && ImGui::IsMouseClicked(ImGuiMouseButton_Right) && !ImGui::IsAnyItemHovered()) {
				m_SelectedEntityID = UUID64::INVALID;
			
				ImGui::OpenPopup("CreationPopup");
				
			}

			if (ImGui::BeginPopup("CreationPopup"))
			{
				ImGui::SeparatorText("Create");

				if (ImGui::BeginMenu("2D"))
				{
					if (ImGui::MenuItem("Quad")) {
						Entity& e = m_Scene->CreateEntity();
						e.AddComponent<SpriteRendererComponent>();

						NameComponent* nameComp = e.GetComponent<NameComponent>();
						nameComp->Text = "Quad";
					}

					if (ImGui::MenuItem("Circle")) {
						Entity& e = m_Scene->CreateEntity();
						e.AddComponent<CircleRendererComponent>();

						NameComponent* nameComp = e.GetComponent<NameComponent>();
						nameComp->Text = "Circle";
					}

					ImGui::EndMenu();
				}

				if (ImGui::Selectable("Empty entity")) {
					m_Scene->CreateEntity();
				}

				ImGui::Separator();
				ImGui::Text("Tooltip here");
				ImGui::SetItemTooltip("I am a tooltip over a popup");

				ImGui::EndPopup();
			}


			ImGui::End();
		}
	}

	void SceneHierarchyPanel::DrawEntityNode(const UUID64& id, const Entity& e)
	{
		NameComponent* nameComp = e.GetComponent<NameComponent>();
		std::string label = "Entity###" + std::to_string(id);

		if (nameComp) {
			label = nameComp->Text + "###" + std::to_string(id);
		}

		ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_OpenOnArrow;

		if (m_SelectedEntityID == id) {
			flags |= ImGuiTreeNodeFlags_Selected; 
		}

		const auto& children = e.GetChildEntities();
		if (children.empty()) {
			flags |= ImGuiTreeNodeFlags_Leaf;
		}

		bool isOpen = ImGui::TreeNodeEx(label.c_str(), flags);

		if (ImGui::IsItemClicked()) {
			if (m_SelectedEntityID != id) {
				m_SelectedEntityID = id;
				//KRX_CORE_TRACE("Entity id: {}", (uint64_t)m_SelectedId);
			}
		}

		if (isOpen) {
			for (UUID64 childId : children) {
				Entity* childEntity = m_Scene->FindByUUID(childId);
				if (childEntity) {
					DrawEntityNode(childId, *childEntity);
				}
			}
			ImGui::TreePop();
		}
	}

}