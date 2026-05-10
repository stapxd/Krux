#include "krxpch.h"
#include "OpenGLVertexArray.h"

#include "Krux/Utils/Utils.h"

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

    void OpenGLVertexArray::AttachVertexBuffer(Ref<VertexBuffer> vbo, const VertexLayout& layout)
    {
        glVertexArrayVertexBuffer(m_RendererID, m_VertexBufferIndex, vbo->GetRendererID(), 0, layout.GetStride());

        int attribIndex = 0;
        GLuint relativeOffset = 0;
        for (auto& el : layout.GetElements()) {
            glEnableVertexArrayAttrib(m_RendererID, attribIndex);

            glVertexArrayAttribFormat(m_RendererID, attribIndex, el.Count, Utils::GetOpenGLTypeFromVertexLayoutType(el.Type), el.Normalized ? GL_TRUE : GL_FALSE, relativeOffset);
            relativeOffset += el.Count * Utils::GetSizeOfVertexLayoutType(el.Type);

            glVertexArrayAttribBinding(m_RendererID, attribIndex, m_VertexBufferIndex);

            attribIndex++;
        }

        m_VertexBufferIndex++;
    }

    void OpenGLVertexArray::AttachElementBuffer(Ref<IndexBuffer> ebo)
    {
        glVertexArrayElementBuffer(m_RendererID, ebo->GetRendererID());
    }

}