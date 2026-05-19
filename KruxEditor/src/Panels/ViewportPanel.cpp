#include "ViewportPanel.h"

#include "Krux/Core/Application.h"

#include <imgui.h>

namespace Krux {

	ViewportPanel::ViewportPanel()
	{}

	void ViewportPanel::OnRender(uint32_t colorAttachment) {
		if (m_IsOpen)
		{
			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
			ImGui::Begin("Viewport", &m_IsOpen, ImGuiWindowFlags_NoScrollbar);


				m_IsFocused = ImGui::IsWindowFocused();

				if (m_IsFocused || ImGui::IsWindowHovered()) {
					Application::Instance()->GetImGuiLayer()->SetBlockEvents(false);
				}
				else
					Application::Instance()->GetImGuiLayer()->SetBlockEvents(true);

				ImVec2 panelSize = ImGui::GetContentRegionAvail();
				m_NewViewportSize = { panelSize.x, panelSize.y };

				ImGui::Image((ImTextureID)colorAttachment, ImVec2(m_ViewportSize.x, m_ViewportSize.y), ImVec2{ 0, 1 }, ImVec2{ 1, 0 });


			ImGui::End();
			ImGui::PopStyleVar();
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