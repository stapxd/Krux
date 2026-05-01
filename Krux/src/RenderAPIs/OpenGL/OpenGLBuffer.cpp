#include "krxpch.h"
#include "OpenGLBuffer.h"

#include "Krux/Core/Core.h"

#include "Krux/Utils/Utils.h"

namespace Krux {

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

    void OpenGLIndexBuffer::SetData(const void* data, uint32_t count, BufferUsage usage)
    {
        glNamedBufferData(m_RendererID, count * sizeof(unsigned int), data, Utils::ConvertBufferUsageToOpenGLBufferUsage(usage));
        m_Count = count;
    }

    uint32_t OpenGLIndexBuffer::GetRendererID() const
    {
        return m_RendererID;
    }

}