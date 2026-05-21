#pragma once

namespace Krux {

	class SceneHierarchyPanel {
	public:
		SceneHierarchyPanel();
		void OnRender();

		bool IsFocused() const { return m_IsFocused; }

		bool* Open() { return &m_IsOpen; }

	private:
		bool m_IsOpen = true;
		bool m_IsFocused = false;
	};

}