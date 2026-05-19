#include "krxpch.h"
#include "OpenGLFrameBuffer.h"

#include "Krux/Core/Core.h"
#include "Krux/Utils/Utils.h"

#include <glad/glad.h>

namespace Krux {

	OpenGLFrameBuffer::OpenGLFrameBuffer(FrameBufferSpecification spec)
	{
		m_Specification = spec;

		Invalidate();
	}

	OpenGLFrameBuffer::~OpenGLFrameBuffer()
	{
		glDeleteFramebuffers(1, &m_RendererID);
		for (uint32_t attachmentID : m_AttachmentIDs)
			glDeleteTextures(1, &attachmentID);
	}

	void OpenGLFrameBuffer::Bind() const
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);
	}

	void OpenGLFrameBuffer::UnBind() const
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void OpenGLFrameBuffer::Resize(uint32_t width, uint32_t height)
	{
		if (width == 0 || height == 0)
			return;

		if (m_Specification.Width == width && m_Specification.Height == height)
			return;

		m_Specification.Width = width;
		m_Specification.Height = height;
		Invalidate();
	}

	void OpenGLFrameBuffer::Invalidate()
	{
		if (m_RendererID) {
			glDeleteFramebuffers(1, &m_RendererID);
			for (uint32_t attachmentID : m_AttachmentIDs)
				glDeleteTextures(1, &attachmentID);

			m_AttachmentIDs.clear();
		}

		m_AttachmentIDs.resize(m_Specification.Attachments.size());

		glCreateFramebuffers(1, &m_RendererID);

		bool depthAttached = false;
		for (size_t i = 0, attCount = 0; i < m_Specification.Attachments.size(); i++) {
			glCreateTextures(GL_TEXTURE_2D, 1, &m_AttachmentIDs[i]);
			glTextureStorage2D(m_AttachmentIDs[i], 1, Utils::FrameBufferAttachmentToOpenGLInternalFormat(m_Specification.Attachments[i]), m_Specification.Width, m_Specification.Height);

			glTextureParameteri(m_AttachmentIDs[i], GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTextureParameteri(m_AttachmentIDs[i], GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTextureParameteri(m_AttachmentIDs[i], GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTextureParameteri(m_AttachmentIDs[i], GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

			AttachmentType currentAttachmentType = Utils::GetAttachmentType(m_Specification.Attachments[i]);
			if (currentAttachmentType == AttachmentType::Color) {
				glNamedFramebufferTexture(m_RendererID, GL_COLOR_ATTACHMENT0 + (GLenum)attCount, m_AttachmentIDs[i], 0);
				attCount++;
			}
			else if (currentAttachmentType == AttachmentType::Depth) {
				KRX_CORE_ASSERT(!depthAttached, "FrameBuffer can only accept one DepthAttachment!");
				glNamedFramebufferTexture(m_RendererID, GL_DEPTH_ATTACHMENT, m_AttachmentIDs[i], 0);
				depthAttached = true;
			}
		}

		if (glCheckNamedFramebufferStatus(m_RendererID, GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		{
			KRX_CORE_ERROR("FrameBuffer is not complete!");
		}
	}

}