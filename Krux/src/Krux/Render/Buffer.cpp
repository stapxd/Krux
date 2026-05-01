#include "krxpch.h"
#include "Buffer.h"

#include "Krux/Core/Core.h"

#include "RenderAPI.h"

#include "RenderAPIs/OpenGL/OpenGLBuffer.h"

namespace Krux {

    // Vertex Buffer ---------------

    Ref<VertexBuffer> VertexBuffer::Create()
    {
		switch (RenderAPI::API())
        {
        case Krux::RenderAPIType::None:
            KRX_CORE_ASSERT(false, "Current version does not support RenderAPIType::None!");
            return nullptr;
        case Krux::RenderAPIType::OpenGL:
            return Ref<OpenGLVertexBuffer>::Create();
        }

        KRX_CORE_ASSERT(false, "Invalid RenderAPIType!");
        return nullptr;
    }

    // Index Buffer ----------------

    Ref<IndexBuffer> IndexBuffer::Create()
    {
        switch (RenderAPI::API())
        {
        case Krux::RenderAPIType::None:
            KRX_CORE_ASSERT(false, "Current version does not support RenderAPIType::None!");
            return nullptr;
        case Krux::RenderAPIType::OpenGL:
            return Ref<OpenGLIndexBuffer>::Create();
        }

        KRX_CORE_ASSERT(false, "Invalid RenderAPIType!");
        return nullptr;
    }

}