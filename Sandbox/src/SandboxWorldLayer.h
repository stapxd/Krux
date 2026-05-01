#pragma once

#include "Krux/Core/Core.h"
#include "Krux/Events/KeyEvents.h"

#include "Krux/Render/Renderer.h"

#include "Krux/Core/Layer.h"

#include <imgui.h>

// TEMP
#include "Krux/Render/Buffer.h"
#include "Krux/Render/VertexArray.h"
#include "Krux/Render/Shader.h"

class SandboxWorldLayer : public Krux::Layer {
public:
	SandboxWorldLayer()
		: Layer("World Layer")
	{}
	
	void OnAttach() override;
	void OnDetach() override;
	void OnImGuiRender() override;
	void OnUpdate() override;
	void OnEvent(Krux::Event& e) override;
	bool OnKeyPressed(Krux::KeyPressedEvent& e);

private:
	Krux::Ref<Krux::VertexArray> VAO;
	Krux::Ref<Krux::VertexBuffer> VBO;
	Krux::Ref<Krux::IndexBuffer> EBO;
	Krux::Ref<Krux::Shader> Shader;
};