#include "krxpch.h"
#include "OpenGLContext.h"

#include "Krux/Core/Core.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Krux {

    OpenGLContext::OpenGLContext(GLFWwindow* window)
    {
        m_Window = window;
    }

    bool OpenGLContext::Init()
    {
        glfwMakeContextCurrent(m_Window);

        if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
            KRX_CORE_ASSERT(false, "Failed to initialize GLAD!");
            return false;
        }

        return true;
    }

    void OpenGLContext::SwapBuffers()
    {
        glfwSwapBuffers(m_Window);
        glfwPollEvents();
    }

}
