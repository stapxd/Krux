#pragma once

#include "Krux/Scene/Scene.h"

#include "Panel.h"

namespace Krux {

	class SceneHierarchyPanel : public Panel {
	public:
		SceneHierarchyPanel(Scene* scene);
		virtual void RenderContent(PanelData panelData = std::monostate{}) override;

		void DrawEntityNode(const UUID64& id, const Entity& e);

		bool* Open() { return &m_IsOpen; }
		UUID64 SelectedEntityID() { return m_SelectedEntityID; }

	private:
		Scene* m_Scene;
		UUID64 m_SelectedEntityID = UUID64::INVALID;
	};

}