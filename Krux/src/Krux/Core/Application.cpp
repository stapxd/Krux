#include "krxpch.h"
#include "Application.h"

#include "Core.h"

#include "System/Windows/WindowsWindow.h"

#include "Krux/Render/RenderAPI.h"
#include "Krux/Render/Renderer.h"

#include <iostream>
#include <functional>

namespace Krux {

	Application::Application(ApplicationSpecification specification)
		: m_Specification(specification)
	{
		s_Instance = this;

		m_Window = CreateApplicationWindow({ specification.Name, specification.Width, specification.Height });
		m_Window->Initialize();
		m_Window->SetEventCallback(BIND_EVENT_FUNC(OnEvent));

		m_Context = RenderContext::Create(RenderAPI::API());

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);

		m_RenderThreadRunning = true;
		m_RenderThread = std::thread(&Application::OnRenderThread, this);
	}

	Application::~Application()
	{
		delete m_Window;
	}

	void Application::OnRenderThread()
	{
		m_Context->Init();
		Renderer::Init();

		while (m_RenderThreadRunning) {
			m_RenderQueue.Execute();
		}

	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher d(e);
		d.Dispatch<WindowCloseEvent>(BIND_EVENT_FUNC(OnWindowClose));
		d.Dispatch<WindowResizeEvent>(BIND_EVENT_FUNC(OnWindowResize));

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
		/*m_RenderQueue.Submit([layer]() {
		});*/
	}

	void Application::PushOverlay(Layer* overlay)
	{
		m_LayerStack.PushOverlay(overlay);
		overlay->OnAttach();
		/*m_RenderQueue.Submit([overlay]() {
		});*/
	}

	void Application::Run()
	{
		while (m_IsRunning) {
			m_RenderQueue.AcquireFrame();

			m_Window->OnUpdate();

			float currentTime = m_Window->GetTime();
			m_Time.SetDeltaTime(currentTime - m_LastFrame);
			m_LastFrame = currentTime;


			m_RenderQueue.Submit([]() {
				Renderer::Clear();
			});

			{
				std::scoped_lock lock(m_LayerStack.GetMutex());
				for (auto it : m_LayerStack) {
					it->OnUpdate(m_Time);

					m_RenderQueue.Submit([it]() {
						it->OnRender();
					});
				}
			}

			m_ImGuiLayer->Begin();
			for (auto it : m_LayerStack) {
				it->OnImGuiRender();
			}
			m_ImGuiLayer->End();
			

			m_RenderQueue.Submit([this]() {
				m_Context->SwapBuffers();
				m_RenderQueue.ReleaseFrame();
			});
		}

		m_RenderQueue.Shutdowm();
		m_RenderThread.join();
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_IsRunning = false;
		return true;
	}

	bool Application::OnWindowResize(WindowResizeEvent& e)
	{
		m_Specification.Width = e.GetWidth();
		m_Specification.Height = e.GetHeight();

		m_RenderQueue.Submit([this]() {
			m_Context->SetViewport(m_Specification.Width, m_Specification.Height);
		});

		return false;
	}
}
