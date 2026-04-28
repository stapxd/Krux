#pragma once

#include "Window.h"

#include "Krux/Events/WindowEvents.h"
#include "Krux/Events/KeyEvents.h"
#include "Krux/Events/MouseEvents.h"

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

		const ApplicationSpecification& GetSpecification() const { return m_Specification; }
		Window* GetWindow() const { return m_Window; }

		void OnEvent(Event& e);
		void Run();

		static Application* Instance() { return m_Instance; }

		bool OnWindowClose(WindowCloseEvent& e);

		//temp
		bool OnWindowResize(WindowResizeEvent& e);
		bool OnWindowMoved(WindowMovedEvent& e);
		bool OnKeyPressed(KeyPressedEvent& e);
		bool OnMouseButtonPressed(MouseButtonPressedEvent& e);
		bool OnMouseScrolled(MouseScrollEvent& e);
		bool OnMouseMoved(MouseMovedEvent& e);

	protected:
		inline static Application* m_Instance = nullptr;

		ApplicationSpecification m_Specification;

		Window* m_Window = nullptr;
		bool m_IsRunning = true;
	};

	Application* CreateApplication();
}

