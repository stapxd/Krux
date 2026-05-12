#pragma once

#include <string>

#include "Krux/Events/Event.h"

namespace Krux {

	struct WindowSpecification {
		std::string Name = "Window";
		int Width = 1600;
		int Height = 900;

		bool IsVSync = false;
	};

	class Window
	{
	public:
		using EventCallback = std::function<void(Event&)>;
	public:
		Window(WindowSpecification windowSpec);
		virtual ~Window() = default;

		const std::string& GetName() { return m_Specification.Name; }

		void SetWidth(int width) { m_Specification.Width = width; }
		inline int GetWidth()  const { return m_Specification.Width;  }

		void SetHeight(int height) { m_Specification.Height = height; }
		inline int GetHeight() const { return m_Specification.Height; }

		bool GetIsVSync() { return m_Specification.IsVSync; }
		virtual void SetVSync(bool value) { m_Specification.IsVSync = value; }

		void SetEventCallback(EventCallback callback) { m_EventCallback = callback; }
		void InvokeEventCallback(Event& e) { m_EventCallback(e); }

		virtual void* GetNativeWindow() = 0;
		virtual float GetTime() = 0;

		virtual void Initialize() = 0;
		virtual void OnUpdate() = 0;

	protected:
		WindowSpecification m_Specification;

		EventCallback m_EventCallback;
	};

	Window* CreateApplicationWindow(WindowSpecification windowSpec);
}

