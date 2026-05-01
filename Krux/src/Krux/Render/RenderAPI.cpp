#include "krxpch.h"

#include "Krux/Core/Core.h"
#include "RenderAPI.h"

#include "RenderAPIs/OpenGL/OpenGLRenderAPI.h"

namespace Krux {

	RenderAPIType RenderAPI::s_API = RenderAPIType::OpenGL;

	Ref<RenderAPI> RenderAPI::Create()
	{
        switch (m_API)
        {
        case Krux::RenderAPIType::None:
            KRX_CORE_ASSERT(false, "Current version does not support RenderAPIType::None!");
            return nullptr;
        case Krux::RenderAPIType::OpenGL:
            return Ref<OpenGLRenderAPI>::Create();
        }

        KRX_CORE_ASSERT(false, "Invalid RenderAPIType!");
        return nullptr;
    }

}