#pragma once

// Core
#include "Krux/Core/Application.h"
#include "Krux/Core/Core.h"
#include "Krux/Core/Time.h"
#include "Krux/Core/Layer.h"

// Events
#include "Krux/Events/KeyEvents.h"
#include "Krux/Events/WindowEvents.h"
#include "Krux/Events/MouseEvents.h"

// Scene
#include "Krux/Scene/Scene.h"

// Render
#include "Krux/Render/Renderer.h"
#include "Krux/Render/FrameBuffer.h"
#include "Krux/Render/OrthographicCamera.h"
#include "Krux/Render/OrthographicCameraController.h"
#include "Krux/Render/Assets/AssetManager.h"
#include "Krux/Render/Assets/Texture2D.h"

// Panels
#include "Panels/ViewportPanel.h"
#include "Panels/SceneHierarchyPanel.h"
#include "Panels/InspectorPanel.h"

#include <imgui.h>

namespace Krux {

	class EditorLayer : public Layer {
	public:
		EditorLayer();

		void OnAttach() override;
		void OnDetach() override;
		void OnImGuiRender() override;
		void OnUpdate(Time time) override;
		void OnEvent(Event& e) override;

		bool OnKeyPressed(KeyPressedEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);
		bool OnMouseScroll(MouseScrollEvent& e);

	private:
		OrthographicCamera m_Camera;
		OrthographicCameraController m_CameraController;

		AssetHandle m_Texture;
		AssetHandle m_Texture2;

		Ref<FrameBuffer> m_FrameBuffer;

		// Scene
		Scene m_Scene;
		UUID64 m_EntityToDelete = UUID64(UUID64::INVALID);

		// Panels
		ViewportPanel m_ViewportPanel;
		SceneHierarchyPanel m_SceneHierarchyPanel;
		InspectorPanel m_InspectorPanel;

	};

}