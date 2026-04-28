#include "Krux/Core/EntryPoint.h"

class SandboxApplication : public Krux::Application {
public:
	SandboxApplication(Krux::ApplicationSpecification specification)
		: Krux::Application(specification)
	{

	}

	~SandboxApplication() {

	}
};

Krux::Application* Krux::CreateApplication() {
	return new SandboxApplication({ "Sandbox123", 1000, 550 });
}