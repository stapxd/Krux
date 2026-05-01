#include "krxpch.h"
#include "OpenGLContext.h"

#include "Krux/Core/Core.h"

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

        glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);
        glEnable(GL_DEBUG_OUTPUT);
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);

        KRX_CORE_INFO("OpenGL Info:");
        //KRX_CORE_INFO("  Vendor: {}", (const char*)glGetString(GL_VENDOR));
        //KRX_CORE_INFO("  Renderer: {}", (const char*)glGetString(GL_RENDERER));
        KRX_CORE_INFO("  Version: {}", (const char*)glGetString(GL_VERSION));

        KRX_CORE_ASSERT(!(GLVersion.major < 4 || GLVersion.minor < 6), "Krux requires OpenGL 4.6!");

        return true;
    }

    void OpenGLContext::SwapBuffers()
    {
        glfwSwapBuffers(m_Window);
        glfwPollEvents();
    }

}
