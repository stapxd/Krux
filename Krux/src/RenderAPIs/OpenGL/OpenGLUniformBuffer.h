#pragma once

#include "Krux/Render/UniformBuffer.h"

namespace Krux {

	class OpenGLUniformBuffer : public UniformBuffer {
	public:
		OpenGLUniformBuffer(uint32_t size, uint32_t binding, BufferUsage usage = BufferUsage::StaticDraw);
		virtual ~OpenGLUniformBuffer() override;

		virtual void SetData(const void* data, uint32_t size, uint32_t offset = 0) override;

		virtual uint32_t GetRendererID() const;

	private:
		uint32_t m_RendererID;
	};

}