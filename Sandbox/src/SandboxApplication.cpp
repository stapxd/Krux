#include "Krux/EntryPoint.h"

class SandboxApplication : public Krux::Application {
public:
	SandboxApplication(Krux::ApplicationSpecification specification)
		: Krux::Application(specification)
	{

	}

	~SandboxApplication() {

	}
};

Krux::Application* Krux::Create() {
	return new SandboxApplication({ "Sandbox" });
}