#pragma once

#include "Krux/Scene/Scene.h"

namespace Krux {

	class SceneHierarchyPanel {
	public:
		SceneHierarchyPanel(Scene* scene);
		void OnRender();

		void DrawEntityNode(const UUID64& id, const Entity& e);

		bool IsFocused() const { return m_IsFocused; }
		bool* Open() { return &m_IsOpen; }

	private:
		bool m_IsOpen = true;
		bool m_IsFocused = false;

		Scene* m_Scene;
		UUID64 m_SelectedId = UUID64::INVALID;
	};

}