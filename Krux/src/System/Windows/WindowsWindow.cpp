#include "krxpch.h"
#include "WindowsWindow.h"

#include "Krux/Core.h"
#include "Krux/Log.h"

namespace Krux {
	WindowsWindow::WindowsWindow(WindowSpecification windowSpec)
		: Window(windowSpec)
	{
        
	}

    WindowsWindow::~WindowsWindow()
    {
        Shutdown();
    }

    void WindowsWindow::SetVSync(bool value)
    {
        m_Specification.IsVSync = value;
        glfwSwapInterval(m_Specification.IsVSync);
    }

    void WindowsWindow::OnUpdate()
    {
        glfwSwapBuffers(m_Window);
        glfwPollEvents();
    }

    void WindowsWindow::Initialize()
    {
        KRX_CORE_ASSERT(glfwInit());

        m_Window = glfwCreateWindow(m_Specification.Width, m_Specification.Height, m_Specification.Name.c_str(), NULL, NULL);
        if (!m_Window)
        {
            glfwTerminate();
            KRX_CORE_ASSERT(false);
        }

        glfwMakeContextCurrent(m_Window);

        glfwSwapInterval(m_Specification.IsVSync);

        KRX_CORE_INFO("Initialized Windows Window: {}, {}:{}", m_Specification.Name, m_Specification.Width, m_Specification.Height);
    }

    void WindowsWindow::Shutdown()
    {
        glfwTerminate();
        m_Window = nullptr;
    }
}
