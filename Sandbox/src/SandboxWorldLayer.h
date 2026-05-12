#pragma once

#include "Krux/Core/Application.h"
#include "Krux/Core/Core.h"
#include "Krux/Core/Time.h"
#include "Krux/Events/KeyEvents.h"

#include "Krux/Render/Renderer.h"

#include "Krux/Core/Layer.h"

#include <imgui.h>

// TEMP
#include "Krux/Render/OrthographicCamera.h"
#include "Krux/Render/Assets/AssetManager.h"
#include "Krux/Render/Assets/Texture2D.h"

class SandboxWorldLayer : public Krux::Layer {
public:
	SandboxWorldLayer()
		: Layer("World Layer"), m_Camera(Krux::Application::Instance()->GetWidth(), Krux::Application::Instance()->GetHeight())
	{}
	
	void OnAttach() override;
	void OnDetach() override;
	void OnImGuiRender() override;
	void OnUpdate(Krux::Time time) override;
	void OnEvent(Krux::Event& e) override;
	bool OnKeyPressed(Krux::KeyPressedEvent& e);

private:
	Krux::OrthographicCamera m_Camera;

	Krux::AssetHandle m_Texture;
	Krux::AssetHandle m_Texture2;
};