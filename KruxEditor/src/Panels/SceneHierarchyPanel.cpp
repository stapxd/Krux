#include "SceneHierarchyPanel.h"

#include "Krux/Scene/Components.h"

#define IMGUI_DEFINE_MATH_OPERATORS
#include <imgui.h>
#include <imgui_internal.h>

namespace Krux {

	SceneHierarchyPanel::SceneHierarchyPanel(Scene* scene)
		: m_Scene(scene), Panel("Scene Hierarchy")
	{
	}

	// TODO: add drag&drop to make entities be children to other
	void SceneHierarchyPanel::RenderContent(PanelData panelData)
	{
		for (const auto& [id, e] : m_Scene->GetEntities()) {
			if (e.IsRoot())
				DrawEntityNode(id, e);
		}

		if (ImGui::BeginDragDropTargetCustom(ImGui::GetCurrentWindow()->Rect(), ImGui::GetCurrentWindow()->ID))
		{
			if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("DND_ENTITY"))
			{
				if (payload->DataSize == sizeof(UUID64)) {
					UUID64 uuid = *(const UUID64*)payload->Data;
					Entity* changableEntity = m_Scene->FindByUUID(uuid);
					changableEntity->BecomeOrphan();
				}
			}
			ImGui::EndDragDropTarget();
		}

		bool clickedOnItem = ImGui::IsAnyItemHovered();

		if (ImGui::IsWindowHovered(ImGuiHoveredFlags_ChildWindows) && !clickedOnItem)
		{
			if (ImGui::IsMouseClicked(ImGuiMouseButton_Left))
				m_Scene->SetSelectedEntityID(UUID64::INVALID);

			if (ImGui::IsMouseClicked(ImGuiMouseButton_Right))
			{
				m_Scene->SetSelectedEntityID(UUID64::INVALID);
				ImGui::OpenPopup("CreationPopup");
			}
		}

		if (ImGui::BeginPopup("CreationPopup"))
		{
			ImGui::SeparatorText("Create");
			if (ImGui::BeginMenu("2D"))
			{
				if (ImGui::MenuItem("Quad")) {
					Entity& e = m_Scene->CreateEntity();
					e.AddComponent<SpriteRendererComponent>();
					e.GetComponent<NameComponent>()->Text = "Quad";
				}
				if (ImGui::MenuItem("Circle")) {
					Entity& e = m_Scene->CreateEntity();
					e.AddComponent<CircleRendererComponent>();
					e.GetComponent<NameComponent>()->Text = "Circle";
				}
				ImGui::EndMenu();
			}
			if (ImGui::Selectable("Empty entity"))
				m_Scene->CreateEntity();

			ImGui::Separator();
			ImGui::Text("Tooltip here");
			ImGui::SetItemTooltip("I am a tooltip over a popup");
			ImGui::EndPopup();
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

		if (m_Scene->GetSelectedEntityID() == id) {
			flags |= ImGuiTreeNodeFlags_Selected; 
		}

		const auto& children = e.GetChildEntities();
		if (children.empty()) {
			flags |= ImGuiTreeNodeFlags_Leaf;
		}

		bool isOpen = ImGui::TreeNodeEx(label.c_str(), flags);

		if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_None))
		{
			ImGui::SetDragDropPayload("DND_ENTITY", &id, sizeof(UUID64));

			ImGui::EndDragDropSource();
		}
		if (ImGui::BeginDragDropTarget())
		{
			if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("DND_ENTITY"))
			{
				if (payload->DataSize == sizeof(UUID64)) {
					UUID64 uuid = *(const UUID64*)payload->Data;
					Entity& changableEntity = const_cast<Entity&>(e);
					changableEntity.AddChild(uuid);
				}
			}
			ImGui::EndDragDropTarget();
		}

		if (ImGui::IsItemClicked()) {
			if (m_Scene->GetSelectedEntityID() != id) {
				m_Scene->SetSelectedEntityID(id);
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