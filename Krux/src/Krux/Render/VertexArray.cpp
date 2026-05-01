#include "krxpch.h"
#include "VertexArray.h"

#include "Krux/Core/Core.h"
#include "RenderAPI.h"

#include "RenderAPIs/OpenGL/OpenGLVertexArray.h"

namespace Krux {

    Ref<VertexArray> VertexArray::Create()
    {
        switch (RenderAPI::API())
        {
        case Krux::RenderAPIType::None:
            KRX_CORE_ASSERT(false, "Current version does not support RenderAPIType::None!");
            return nullptr;
        case Krux::RenderAPIType::OpenGL:
            return Ref<OpenGLVertexArray>::Create();
        }

        KRX_CORE_ASSERT(false, "Invalid RenderAPIType!");
        return nullptr;
    }

}