#pragma once

#include "Panel.h"

#include "Krux/Scene/Scene.h"
#include "Krux/Render/Cameras/Camera.h"

#include <glm/glm.hpp>

namespace Krux {

	struct ViewportData {
		uint32_t ColorAttachmentID = 0;
		Scene* Scene = nullptr;
		Camera* Camera = nullptr;
	};

	class ViewportPanel : public Panel {
	public:
		ViewportPanel(ViewportData data = {});
		virtual void BeforeWindowSettings() override;
		virtual void AfterWindowSettings() override;
		virtual void RenderContent(PanelData panelData = std::monostate{}) override;
		bool ShouldUpdateExternalViewport();

		glm::vec2 GetSize() { return m_ViewportSize; }

	private:
		glm::vec2 m_ViewportSize = glm::vec2(0.0f);
		glm::vec2 m_NewViewportSize = glm::vec2(0.0f);

		ViewportData m_ViewportData;

	};

}