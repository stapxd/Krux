#pragma once

#include "Krux/Render/FrameBuffer.h"

namespace Krux {

	class OpenGLFrameBuffer : public FrameBuffer {
	public:
		OpenGLFrameBuffer(FrameBufferSpecification spec);
		virtual ~OpenGLFrameBuffer() override;

		virtual void Bind() const override;
		virtual void UnBind() const override;
		virtual int  ReadPixel(uint32_t attachmentIndex, int posX, int posY) const override;
		virtual void ClearAttachment(uint32_t attachmentIndex, void* data) override;

		virtual void Resize(uint32_t width, uint32_t height);
		virtual void Invalidate() override;

		virtual uint32_t GetRendererID() const { return m_RendererID; }
	private:
		uint32_t m_RendererID = 0;
	};

}