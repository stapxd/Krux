#pragma once

#include "Window.h"
#include "Time.h"

#include "Krux/ImGui/ImGuiLayer.h"
#include "LayerStack.h"

#include "Krux/Events/WindowEvents.h"
#include "Krux/Events/KeyEvents.h"
#include "Krux/Events/MouseEvents.h"

#include "Ref.h"

#include "Krux/Render/RenderContext.h"
#include "Krux/Render/RenderQueue.h"

#include <iostream>
#include <condition_variable>

namespace Krux {

	struct ApplicationSpecification {
		std::string Name = "Krux Application";
		int Width = 1600;
		int Height = 900;
	};

	class Application
	{
	public:
		Application(ApplicationSpecification specification);
		virtual ~Application();
		
		static Application* Instance() { return s_Instance; }

		const ApplicationSpecification& GetSpecification() const { return m_Specification; }
		int GetWidth()  { return m_Specification.Width;  }
		int GetHeight() { return m_Specification.Height; }
		Window* GetWindow() const { return m_Window; }

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		void OnRenderThread();
		void Run();

		void OnEvent(Event& e);
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);

	protected:
		inline static Application* s_Instance = nullptr;

		ApplicationSpecification m_Specification;

		// Render
		Ref<RenderContext> m_Context;
		std::atomic<bool> m_RenderThreadRunning{ false };
		std::thread m_RenderThread;
		RenderQueue m_RenderQueue;
		std::mutex m_InitMutex;
		std::condition_variable m_InitCV;
		bool m_RenderThreadReady = false;

		float m_LastFrame = 0.0f;
		Time m_Time;
		Window* m_Window = nullptr;
		bool m_IsRunning = true;

		ImGuiLayer* m_ImGuiLayer;
		LayerStack m_LayerStack;
	};

	Application* CreateApplication();
}

