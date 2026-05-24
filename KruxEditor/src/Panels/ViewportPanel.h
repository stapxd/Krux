#pragma once

#include "Panel.h"

#include <glm/glm.hpp>

namespace Krux {

	class ViewportPanel : public Panel {
	public:
		ViewportPanel();
		virtual void PushWindowStyles() override;
		virtual void PopWindowStyles() override;
		virtual void RenderContent(PanelData panelData = std::monostate{}) override;
		bool ShouldUpdateExternalViewport();

		glm::vec2 GetSize() { return m_ViewportSize; }

	private:
		bool m_IsOpen = true;
		bool m_IsFocused = false;
		bool m_IsHovered = false;

		glm::vec2 m_ViewportSize = glm::vec2(0.0f);
		glm::vec2 m_NewViewportSize = glm::vec2(0.0f);
	};

}