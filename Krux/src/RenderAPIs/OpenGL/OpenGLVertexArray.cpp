#include "krxpch.h"
#include "OpenGLVertexArray.h"

#include <glad/glad.h>

namespace Krux {
    OpenGLVertexArray::OpenGLVertexArray()
    {
        glCreateVertexArrays(1, &m_RendererID);
    }

    OpenGLVertexArray::~OpenGLVertexArray()
    {
        glDeleteVertexArrays(1, &m_RendererID);
    }

    void OpenGLVertexArray::Bind() const
    {
        glBindVertexArray(m_RendererID);
    }

    void OpenGLVertexArray::UnBind() const
    {
        glBindVertexArray(0);
    }

    void OpenGLVertexArray::AttachVertexBuffer(Ref<VertexBuffer> vbo) // add layout
    {
        glVertexArrayVertexBuffer(m_RendererID, m_VertexBufferIndex, vbo->GetRendererID(), 0, 3 * sizeof(float)); // change stride via layout
        m_VertexBufferIndex++;
    }

    void OpenGLVertexArray::AttachElementBuffer(Ref<IndexBuffer> ebo)
    {
        glVertexArrayElementBuffer(m_RendererID, ebo->GetRendererID());
    }

}