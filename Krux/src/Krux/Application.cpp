#include "Application.h"

namespace Krux {

	Application::Application(ApplicationSpecification specification)
		: m_Specification(specification)
	{
		m_Instance = this;
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		std::cout << "app run\n";
	}

}
