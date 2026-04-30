#pragma once

#include "Window.h"

#include "Krux/ImGui/ImGuiLayer.h"
#include "LayerStack.h"

#include "Krux/Events/WindowEvents.h"
#include "Krux/Events/KeyEvents.h"
#include "Krux/Events/MouseEvents.h"

#include "Ref.h"

#include "Krux/Render/RenderContext.h"

#include <iostream>

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
		
		static Application* Instance() { return m_Instance; }

		const ApplicationSpecification& GetSpecification() const { return m_Specification; }
		Window* GetWindow() const { return m_Window; }

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		void Run();

		void OnEvent(Event& e);
		bool OnWindowClose(WindowCloseEvent& e);

	protected:
		inline static Application* m_Instance = nullptr;

		ApplicationSpecification m_Specification;

		Ref<RenderContext> m_Context;

		Window* m_Window = nullptr;
		bool m_IsRunning = true;

		ImGuiLayer* m_ImGuiLayer;
		LayerStack m_LayerStack;
	};

	Application* CreateApplication();
}

