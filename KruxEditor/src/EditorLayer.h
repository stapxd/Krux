#pragma once

#include "Krux/Core/Application.h"
#include "Krux/Core/Core.h"
#include "Krux/Core/Time.h"

#include "Krux/Events/KeyEvents.h"
#include "Krux/Events/WindowEvents.h"
#include "Krux/Events/MouseEvents.h"

#include "Krux/Render/Renderer.h"

#include "Krux/Core/Layer.h"

#include "Krux/Render/OrthographicCamera.h"
#include "Krux/Render/OrthographicCameraController.h"
#include "Krux/Render/Assets/AssetManager.h"
#include "Krux/Render/Assets/Texture2D.h"

#include <imgui.h>

namespace Krux {

	class EditorLayer : public Layer {
	public:
		EditorLayer()
		: Layer("Editor Layer"), m_Camera(Krux::Application::Instance()->GetWidth(), Application::Instance()->GetHeight()), m_CameraController(m_Camera)
		{}

		void OnAttach() override;
		void OnDetach() override;
		void OnImGuiRender() override;
		void OnUpdate(Krux::Time time) override;
		void OnEvent(Krux::Event& e) override;

		bool OnKeyPressed(Krux::KeyPressedEvent& e);
		bool OnWindowResize(Krux::WindowResizeEvent& e);
		bool OnMouseScroll(Krux::MouseScrollEvent& e);

	private:
		OrthographicCamera m_Camera;
		OrthographicCameraController m_CameraController;

		AssetHandle m_Texture;
		AssetHandle m_Texture2;


	};

}