#include "krxpch.h"
#include "Application.h"

#include "System/Windows/WindowsWindow.h"

namespace Krux {

	#ifdef KRX_SYS_WINDOWS
		Window* CreateApplicationWindow(WindowSpecification windowSpec) {
			return new WindowsWindow(windowSpec);
		}
	#endif

	Application::Application(ApplicationSpecification specification)
		: m_Specification(specification)
	{
		m_Instance = this;

		m_Window = CreateApplicationWindow({ specification.Name, specification.Width, specification.Height });
		m_Window->Initialize();
	}

	Application::~Application()
	{
		delete m_Window;
	}

	void Application::Run()
	{
		while (m_IsRunning) {
			m_Window->OnUpdate();
		}
	}

}
