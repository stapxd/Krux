#include "krxpch.h"
#include "UniformBuffer.h"

#include "Krux/Core/Core.h"
#include "RenderAPI.h"

#include "RenderAPIs/OpenGL/OpenGLUniformBuffer.h"

namespace Krux {

    Ref<UniformBuffer> UniformBuffer::Create(uint32_t size, uint32_t binding, BufferUsage usage)
    {
        switch (RenderAPI::API())
        {
        case Krux::RenderAPIType::None:
            KRX_CORE_ASSERT(false, "Current version does not support RenderAPIType::None!");
            return nullptr;
        case Krux::RenderAPIType::OpenGL:
            return Ref<OpenGLUniformBuffer>::Create(size, binding, usage);
        }

        KRX_CORE_ASSERT(false, "Invalid RenderAPIType!");
        return nullptr;
    }

}