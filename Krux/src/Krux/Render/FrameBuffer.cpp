#include "krxpch.h"
#include "FrameBuffer.h"

#include "Krux/Core/Core.h"
#include "RenderAPI.h"

#include "RenderAPIs/OpenGL/OpenGLFrameBuffer.h"

namespace Krux {
    
    uint32_t FrameBuffer::GetAttachmentID(size_t index)
    {
        if (index < 0 || index >= m_AttachmentIDs.size())
            KRX_CORE_ASSERT(false, "FrameBuffer attachment index is out of bounds!");
        
        return m_AttachmentIDs[index];
    }

    Ref<FrameBuffer> FrameBuffer::Create(FrameBufferSpecification spec)
    {
        switch (RenderAPI::API())
        {
        case Krux::RenderAPIType::None:
            KRX_CORE_ASSERT(false, "Current version does not support RenderAPIType::None!");
            return nullptr;
        case Krux::RenderAPIType::OpenGL:
            return Ref<OpenGLFrameBuffer>::Create(spec);
        }

        KRX_CORE_ASSERT(false, "Invalid RenderAPIType!");
        return nullptr;
    }

}