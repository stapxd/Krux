#pragma once

#include "Krux/Core/Window.h"

#include <GLFW/glfw3.h>

namespace Krux {

	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(WindowSpecification windowSpec);
		~WindowsWindow();

		virtual void* GetNativeWindow() override { return m_Window; }

		virtual void Initialize() override;
		virtual void OnUpdate() override;

		virtual void SetVSync(bool value) override;

	private:
		void Shutdown();

	private:
		GLFWwindow* m_Window = nullptr;
	};
}

