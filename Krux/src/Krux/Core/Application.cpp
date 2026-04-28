#include "krxpch.h"
#include "Application.h"

#include "Core.h"

#include "System/Windows/WindowsWindow.h"

#include <iostream>
#include <functional>

namespace Krux {

	Application::Application(ApplicationSpecification specification)
		: m_Specification(specification)
	{
		m_Instance = this;

		m_Window = CreateApplicationWindow({ specification.Name, specification.Width, specification.Height });
		m_Window->Initialize();
		m_Window->SetEventCallback(BIND_EVENT_FUNC(OnEvent));

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);
	}

	Application::~Application()
	{
		delete m_Window;
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher d(e);
		d.Dispatch<WindowCloseEvent>(BIND_EVENT_FUNC(OnWindowClose));

		for (auto it = m_LayerStack.rbegin(); it != m_LayerStack.rend(); it++) {
			(*it)->OnEvent(e);
			if (e.IsHandled)
				break;
		}
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* overlay)
	{
		m_LayerStack.PushOverlay(overlay);
		overlay->OnAttach();
	}

	void Application::Run()
	{
		while (m_IsRunning) {

			for (auto it : m_LayerStack) {
				it->OnUpdate();
			}

			m_ImGuiLayer->Begin();
			for (auto it : m_LayerStack) {
				it->OnImGuiRender();
			}
			m_ImGuiLayer->End();

			m_Window->OnUpdate();
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_IsRunning = false;
		return true;
	}
}
