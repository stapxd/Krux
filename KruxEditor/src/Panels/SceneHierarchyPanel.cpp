#include "SceneHierarchyPanel.h"

#include <imgui.h>

namespace Krux {

	SceneHierarchyPanel::SceneHierarchyPanel()
	{

	}

	void SceneHierarchyPanel::OnRender()
	{
		if (m_IsOpen) {
			ImGui::Begin("Scene Hierarchy", &m_IsOpen);
				
			ImGui::End();
		}
	}

}