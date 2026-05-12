#include "krxpch.h"
#include "OpenGLUniformBuffer.h"

#include "Krux/Utils/Utils.h"

#include <glad/glad.h>

namespace Krux {

	OpenGLUniformBuffer::OpenGLUniformBuffer(uint32_t size, uint32_t binding, BufferUsage usage)
	{
		glCreateBuffers(1, &m_RendererID);
		glNamedBufferData(m_RendererID, size, NULL, Utils::ConvertBufferUsageToOpenGLBufferUsage(usage));
		glBindBufferBase(GL_UNIFORM_BUFFER, binding, m_RendererID);
	}

	OpenGLUniformBuffer::~OpenGLUniformBuffer()
	{
		glDeleteBuffers(1, &m_RendererID);
	}

	void OpenGLUniformBuffer::SetData(const void* data, uint32_t size, uint32_t offset)
	{
		glNamedBufferSubData(m_RendererID, offset, size, data);
	}

	uint32_t OpenGLUniformBuffer::GetRendererID() const
	{
		return m_RendererID;
	}

}
