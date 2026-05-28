#pragma once

#include "Panel.h"

#include "Krux/Scene/Scene.h"
#include "Krux/Render/Cameras/Camera.h"

#include <glm/glm.hpp>

namespace Krux {

	enum class GuizmoOperation {
		NONE                = 0,
		// from ImGuizmo.h
		TRANSLATE_X			= (1u << 0),
		TRANSLATE_Y			= (1u << 1),
		TRANSLATE_Z			= (1u << 2),
		ROTATE_X			= (1u << 3),
		ROTATE_Y			= (1u << 4),
		ROTATE_Z			= (1u << 5),
		ROTATE_SCREEN		= (1u << 6),
		SCALE_X				= (1u << 7),
		SCALE_Y				= (1u << 8),
		SCALE_Z				= (1u << 9),
		BOUNDS				= (1u << 10),
		SCALE_XU			= (1u << 11),
		SCALE_YU			= (1u << 12),
		SCALE_ZU			= (1u << 13),

		TRANSLATE			= TRANSLATE_X | TRANSLATE_Y | TRANSLATE_Z,
		ROTATE				= ROTATE_X | ROTATE_Y | ROTATE_Z | ROTATE_SCREEN,
		SCALE				= SCALE_X | SCALE_Y | SCALE_Z,
		SCALEU				= SCALE_XU | SCALE_YU | SCALE_ZU, // universal
		UNIVERSAL			= TRANSLATE | ROTATE | SCALEU
	};

	enum class GuizmoMode
	{
		LOCAL,
		WORLD
	};

	struct ViewportData {
		uint32_t ColorAttachmentID = 0;
		Scene* Scene = nullptr;
		Camera* Camera = nullptr;

		GuizmoOperation CurrentOperation = GuizmoOperation::TRANSLATE;
	};

	class ViewportPanel : public Panel {
	public:
		ViewportPanel(ViewportData data = {});
		virtual void BeforeWindowSettings() override;
		virtual void AfterWindowSettings() override;
		virtual void RenderContent(PanelData panelData = std::monostate{}) override;
		bool ShouldUpdateExternalViewport();

		void SetGuizmoOperation(GuizmoOperation operation) { m_ViewportData.CurrentOperation = operation; }

		glm::vec2 GetSize() { return m_ViewportSize; }

	private:
		glm::vec2 m_ViewportSize = glm::vec2(0.0f);
		glm::vec2 m_NewViewportSize = glm::vec2(0.0f);

		ViewportData m_ViewportData;
	};

}

inline Krux::GuizmoOperation operator|(Krux::GuizmoOperation lhs, Krux::GuizmoOperation rhs)
{
	return static_cast<Krux::GuizmoOperation>(static_cast<int>(lhs) | static_cast<int>(rhs));
}