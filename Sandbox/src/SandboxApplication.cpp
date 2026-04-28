#include "Krux/Core/EntryPoint.h"

#include "SandboxWorldLayer.h"

class SandboxApplication : public Krux::Application {
public:
	SandboxApplication(Krux::ApplicationSpecification specification)
		: Krux::Application(specification)
	{
		PushLayer(new SandboxWorldLayer());
	}

	~SandboxApplication() {

	}
};

Krux::Application* Krux::CreateApplication() {
	return new SandboxApplication({ "Sandbox123", 1000, 550 });
}