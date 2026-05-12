#include "krxpch.h"
#include "WindowsWindow.h"

#include "Krux/Core/Core.h"
#include "Krux/Core/Log.h"

#include "Krux/Events/WindowEvents.h"
#include "Krux/Events/KeyEvents.h"
#include "Krux/Events/MouseEvents.h"

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

    float WindowsWindow::GetTime()
    {
        return (float)glfwGetTime();
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

        glfwSwapInterval(m_Specification.IsVSync);

        KRX_CORE_INFO("Initialized Windows Window: {}, {}:{}", m_Specification.Name, m_Specification.Width, m_Specification.Height);

        glfwSetWindowUserPointer(m_Window, this);
        // Window Events
        {
            glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window) {
                auto& self = *(Window*)glfwGetWindowUserPointer(window);

                WindowCloseEvent e;
                self.InvokeEventCallback(e);
                });

            glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height) {
                auto& self = *(Window*)glfwGetWindowUserPointer(window);
                self.SetWidth(width);
                self.SetHeight(height);

                WindowResizeEvent e(width, height);
                self.InvokeEventCallback(e);
                });

            glfwSetWindowPosCallback(m_Window, [](GLFWwindow* window, int xpos, int ypos)
            {
                auto& self = *(Window*)glfwGetWindowUserPointer(window);

                WindowMovedEvent e(xpos, ypos);
                self.InvokeEventCallback(e);
            });
        }

        // Key Events
        {
            glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
                {
                    auto& self = *(Window*)glfwGetWindowUserPointer(window);

                    switch (action)
                    {
                    case GLFW_PRESS: {
                        KeyPressedEvent e(key, 0);
                        self.InvokeEventCallback(e);
                        break;
                    }
                    case GLFW_REPEAT: {
                        KeyPressedEvent e(key, 1);
                        self.InvokeEventCallback(e);
                        break;
                    }
                    case GLFW_RELEASE: {
                        KeyReleasedEvent e(key);
                        self.InvokeEventCallback(e);
                        break;
                    }
                    default:
                        KRX_CORE_ASSERT(false, "Unknown Key Event Action");
                        break;
                    }
                });
        }

        // Mouse Events
        {
            glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
            {
                auto& self = *(Window*)glfwGetWindowUserPointer(window);

                switch (action)
                {
                case GLFW_PRESS: {
                    MouseButtonPressedEvent e(button);
                    self.InvokeEventCallback(e);
                    break;
                }
                case GLFW_RELEASE: {
                    MouseButtonReleasedEvent e(button);
                    self.InvokeEventCallback(e);
                    break;
                }
                default:
                    KRX_CORE_ASSERT(false, "Unknown Key Event Action");
                    break;
                }
            });

            glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xoffset, double yoffset)
            {
                auto& self = *(Window*)glfwGetWindowUserPointer(window);

                MouseScrollEvent e(xoffset, yoffset);
                self.InvokeEventCallback(e);
            });

            glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xpos, double ypos)
            {
                auto& self = *(Window*)glfwGetWindowUserPointer(window);

                MouseMovedEvent e(xpos, ypos);
                self.InvokeEventCallback(e);
            });
        }
    }

    void WindowsWindow::Shutdown()
    {
        glfwTerminate();
        m_Window = nullptr;
    }
}
