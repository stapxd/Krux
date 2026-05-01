#include "krxpch.h"
#include "OpenGLBuffer.h"

#include "Krux/Core/Core.h"

#include <glad/glad.h>

namespace Krux {

    namespace Utils {
        GLenum ConvertBufferUsageToOpenGLBufferUsage(BufferUsage usage) {
            switch (usage)
            {
            case Krux::BufferUsage::StreamDraw:
                return GL_STREAM_DRAW;
            case Krux::BufferUsage::StaticDraw:
                return GL_STATIC_DRAW;
            case Krux::BufferUsage::DynamicDraw:
                return GL_DYNAMIC_DRAW;
            }

            KRX_CORE_ASSERT(false, "Invalid BufferUsage!");
            return 0;
        }
    }

    // Vertex Buffer ----------------

    OpenGLVertexBuffer::OpenGLVertexBuffer()
    {
        glCreateBuffers(1, &m_RendererID);
    }

    OpenGLVertexBuffer::~OpenGLVertexBuffer()
    {
        glDeleteBuffers(1, &m_RendererID);
    }

    void OpenGLVertexBuffer::Bind() const
    {
        
    }

    void OpenGLVertexBuffer::UnBind() const
    {

    }

    void OpenGLVertexBuffer::SetData(const void* data, uint32_t size, BufferUsage usage) const
    {
        glNamedBufferData(m_RendererID, size, data, Utils::ConvertBufferUsageToOpenGLBufferUsage(usage));
    }

    uint32_t OpenGLVertexBuffer::GetRendererID() const
    {
        return m_RendererID;
    }

    // Index Buffer ----------------

    OpenGLIndexBuffer::OpenGLIndexBuffer()
    {
        glCreateBuffers(1, &m_RendererID);
    }

    OpenGLIndexBuffer::~OpenGLIndexBuffer()
    {
        glDeleteBuffers(1, &m_RendererID);
    }

    void OpenGLIndexBuffer::Bind() const
    {
    }

    void OpenGLIndexBuffer::UnBind() const
    {
    }

    void OpenGLIndexBuffer::SetData(const void* data, uint32_t count, BufferUsage usage) const
    {
        glNamedBufferData(m_RendererID, count * sizeof(unsigned int), data, Utils::ConvertBufferUsageToOpenGLBufferUsage(usage));
    }

    uint32_t OpenGLIndexBuffer::GetRendererID() const
    {
        return m_RendererID;
    }

}