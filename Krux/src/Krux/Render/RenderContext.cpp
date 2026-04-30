#include "krxpch.h"
#include "Krux/Core/Core.h"
#include "RenderContext.h"

#include "RenderAPIs/OpenGL/OpenGLContext.h"

#include "Krux/Core/Application.h"

namespace  Krux {

    Ref<RenderContext> RenderContext::Create(RenderAPIType type)
    {
        switch (type)
        {
        case Krux::RenderAPIType::None:
            KRX_CORE_ASSERT(false, "Current version does not support RenderAPIType::None!");
            return nullptr;
        case Krux::RenderAPIType::OpenGL:
            return Ref<OpenGLContext>::Create((GLFWwindow*)Application::Instance()->GetWindow()->GetNativeWindow());
        }

        KRX_CORE_ASSERT(false, "Invalid RenderAPIType!");
        return nullptr;
    }

}
