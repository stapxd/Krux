#pragma once

#include "Krux/Core/Core.h"
#include "Krux/Events/KeyEvents.h"

class SandboxWorldLayer : public Krux::Layer {
public:
	SandboxWorldLayer()
		: Layer("World Layer")
	{}

	void OnAttach() override {
		KRX_TRACE("Attached Sandbox World Layer");
	}

	void OnDetach() override {
		KRX_TRACE("Detached Sandbox World Layer");
	}

	void OnEvent(Krux::Event& e) override {
		Krux::EventDispatcher d(e);

		d.Dispatch<Krux::KeyPressedEvent>(BIND_EVENT_FUNC(OnKeyPressed));
	}

	bool OnKeyPressed(Krux::KeyPressedEvent& e)
	{
		KRX_CORE_TRACE("{}", (char)e.GetKey());
		return true;
	}
};