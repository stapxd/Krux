#include "krxpch.h"
#include "Application.h"

#include "Core.h"

#include "System/Windows/WindowsWindow.h"

#include <iostream>
#include <functional>

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
		m_Window->SetEventCallback(BIND_EVENT_FUNC(OnEvent));
	}

	Application::~Application()
	{
		delete m_Window;
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher d(e);
		d.Dispatch<WindowCloseEvent>(BIND_EVENT_FUNC(OnWindowClose));

		d.Dispatch<WindowResizeEvent>(BIND_EVENT_FUNC(OnWindowResize));
		d.Dispatch<WindowMovedEvent>(BIND_EVENT_FUNC(OnWindowMoved));
		d.Dispatch<KeyPressedEvent>(BIND_EVENT_FUNC(OnKeyPressed));
		d.Dispatch<MouseButtonPressedEvent>(BIND_EVENT_FUNC(OnMouseButtonPressed));
		d.Dispatch<MouseScrollEvent>(BIND_EVENT_FUNC(OnMouseScrolled));
		d.Dispatch<MouseMovedEvent>(BIND_EVENT_FUNC(OnMouseMoved));
	}

	void Application::Run()
	{
		while (m_IsRunning) {
			m_Window->OnUpdate();
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_IsRunning = false;
		return true;
	}

	bool Application::OnWindowResize(WindowResizeEvent& e)
	{
		KRX_CORE_TRACE("x: {} y: {}", e.GetWidth(), e.GetHeight());
		return true;
	}

	bool Application::OnWindowMoved(WindowMovedEvent& e)
	{
		KRX_CORE_TRACE("x: {} y: {}", e.GetXPos(), e.GetYPos());
		return true;
	}

	bool Application::OnKeyPressed(KeyPressedEvent& e)
	{
		KRX_CORE_TRACE("{}", (char)e.GetKey());
		return true;
	}

	bool Application::OnMouseButtonPressed(MouseButtonPressedEvent& e)
	{
		KRX_CORE_TRACE("{}", e.GetKey());
		return true;
	}

	bool Application::OnMouseScrolled(MouseScrollEvent& e)
	{
		KRX_CORE_TRACE("x= {} : y= {}", e.GetXOffset(), e.GetYOffset());
		return true;
	}

	bool Application::OnMouseMoved(MouseMovedEvent& e)
	{
		KRX_CORE_TRACE("x= {} : y= {}", e.GetXPos(), e.GetYPos());
		return true;
	}
}
