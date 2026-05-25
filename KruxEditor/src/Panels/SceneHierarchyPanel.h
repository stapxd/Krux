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

	private:
		Scene* m_Scene;
	};

}