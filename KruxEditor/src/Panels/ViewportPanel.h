#pragma once

#include <glm/glm.hpp>

namespace Krux {

	class ViewportPanel {
	public:
		ViewportPanel();
		void OnRender(uint32_t colorAttachment);
		bool ShouldUpdateExternalViewport();

		glm::vec2 GetSize() { return m_ViewportSize; }
		bool IsFocused() const { return m_IsFocused; }

		bool* Open() { return &m_IsOpen; }

	private:
		bool m_IsOpen = true;
		bool m_IsFocused = false;

		glm::vec2 m_ViewportSize = glm::vec2(0.0f);
		glm::vec2 m_NewViewportSize = glm::vec2(0.0f);
	};

}