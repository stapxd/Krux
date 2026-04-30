#pragma once

#include "Krux/Core/Core.h"
#include "Krux/Events/KeyEvents.h"

#include "Krux/Render/Renderer.h"

#include "Krux/Core/Layer.h"

#include <imgui.h>

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
	uint32_t VAO;
	uint32_t VBO;
	uint32_t IBO;
};