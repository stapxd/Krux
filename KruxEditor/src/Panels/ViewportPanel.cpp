#include "ViewportPanel.h"

#include "Krux/Core/Application.h"
#include "Krux/Math/Math.h"
#include "Krux/Scene/Components.h"

#include <imgui.h>
#include <ImGuizmo.h>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/matrix_decompose.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Krux {

	ViewportPanel::ViewportPanel(ViewportData data)
		: Panel("Viewport"), m_ViewportData(data)
	{}

	void ViewportPanel::BeforeWindowSettings() {
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
	}

	void ViewportPanel::AfterWindowSettings() {
		ImGui::PopStyleVar();
	}

	void ViewportPanel::RenderContent(PanelData panelData) {

		if (std::holds_alternative<uint32_t>(panelData)) {
			
			m_ViewportData.ColorAttachmentID = std::get<uint32_t>(panelData);
			ImVec2 panelSize = ImGui::GetContentRegionAvail();
			m_NewViewportSize = { panelSize.x, panelSize.y };

			ImGui::Image((ImTextureID)m_ViewportData.ColorAttachmentID, panelSize, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });
			
			if (m_ViewportData.Scene->GetState() == SceneState::Edit && m_ViewportData.Scene->GetSelectedEntityID() != UUID64::INVALID) {
				ImGuizmo::Enable(true);
				ImGuizmo::SetOrthographic(false);
				ImGuizmo::SetDrawlist();

				ImVec2 viewportPos = ImGui::GetWindowPos();
				ImVec2 contentMin = ImGui::GetWindowContentRegionMin();
				ImGuizmo::SetRect(viewportPos.x + contentMin.x, viewportPos.y + contentMin.y, panelSize.x, panelSize.y);
				
				TransformComponent* selectedEntTrm = m_ViewportData.Scene->GetComponent<TransformComponent>(m_ViewportData.Scene->GetSelectedEntityID());
				glm::mat4 rotation = glm::toMat4(glm::quat(selectedEntTrm->Rotation));

				glm::mat4 selectedEntTrmMat4 = selectedEntTrm->GetTransform();

				ImGuizmo::Manipulate(
					glm::value_ptr(m_ViewportData.Camera->GetView()),
					glm::value_ptr(m_ViewportData.Camera->GetProjection()),
					ImGuizmo::OPERATION(m_ViewportData.CurrentOperation),
					ImGuizmo::MODE(GuizmoMode::LOCAL),
					glm::value_ptr(selectedEntTrmMat4),
					nullptr,
					nullptr
				);

				if (ImGuizmo::IsUsing()) {
					glm::vec3 newWorldPosition, newScale, newRotation;

					if (!Math::DecomposeTransform(selectedEntTrmMat4, newWorldPosition, newRotation, newScale))
						return;

					if (glm::any(glm::isnan(newWorldPosition)) || glm::any(glm::isnan(newScale)))
						return;

					glm::vec3 parentWorldPosition = glm::vec3(0.0f);
					Entity* selectedEntity = m_ViewportData.Scene->FindByUUID(
						m_ViewportData.Scene->GetSelectedEntityID()
					);
					if (selectedEntity && !selectedEntity->IsRoot()) {
						Entity* parent = selectedEntity->GetParent();
						if (parent)
							parentWorldPosition = parent->GetComponent<TransformComponent>()->WorldPosition;
					}

					selectedEntTrm->LocalPosition = newWorldPosition - parentWorldPosition;
					selectedEntTrm->Rotation = glm::radians(newRotation); 
					selectedEntTrm->Scale = newScale;
					m_ViewportData.Scene->UpdateWorldPositions();
				}

			}

		}

	}

	bool ViewportPanel::ShouldUpdateExternalViewport() {
		if (m_NewViewportSize.x > 0.0f && m_NewViewportSize.y > 0.0f && m_ViewportSize != m_NewViewportSize) {
			m_ViewportSize = m_NewViewportSize;
			return true;
		}
		return false;
	}

}