#include "ViewportPanel.h"

#include "Krux/Core/Application.h"

#include <imgui.h>

namespace Krux {

	ViewportPanel::ViewportPanel()
		: Panel("Viewport")
	{}

	void ViewportPanel::PushWindowStyles() {
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
	}

	void ViewportPanel::PopWindowStyles() {
		ImGui::PopStyleVar();
	}

	void ViewportPanel::RenderContent(PanelData panelData) {

		if (std::holds_alternative<uint32_t>(panelData)) {
			uint32_t colorAttachment = std::get<uint32_t>(panelData);
			ImVec2 panelSize = ImGui::GetContentRegionAvail();
			m_NewViewportSize = { panelSize.x, panelSize.y };

			ImGui::Image((ImTextureID)colorAttachment, ImVec2(m_ViewportSize.x, m_ViewportSize.y), ImVec2{ 0, 1 }, ImVec2{ 1, 0 });
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