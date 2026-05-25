#include "Panel.h"

#include "Krux/Core/Application.h"

#include <imgui.h>

namespace Krux {


	Panel::Panel(const std::string& name)
		: m_Name(name)
	{}

	void Panel::OnRender(PanelData panelData, ImGuiWindowFlags flags) {

		if (m_IsOpen) {
			PushWindowStyles();
			ImGui::Begin(m_Name.c_str(), &m_IsOpen, flags);

			m_IsFocused = ImGui::IsWindowFocused();
			m_IsHovered = ImGui::IsWindowHovered();

			if (m_IsFocused || m_IsHovered) {
				Application::Instance()->GetImGuiLayer()->SetBlockEvents(false);
			}
			else
				Application::Instance()->GetImGuiLayer()->SetBlockEvents(true);

			RenderContent(panelData);

			ImGui::End();
			PopWindowStyles();
		}
	}

}