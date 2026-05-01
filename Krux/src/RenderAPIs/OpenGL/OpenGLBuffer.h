#pragma once

#include "Krux/Render/Buffer.h"

namespace Krux {

	// Vertex Buffer ----------------

	class OpenGLVertexBuffer : public VertexBuffer {
	public:
		OpenGLVertexBuffer();
		virtual ~OpenGLVertexBuffer() override;

		virtual void Bind() const override;
		virtual void UnBind() const override;

		virtual void SetData(const void* data, uint32_t size, BufferUsage usage) const override;

		virtual uint32_t GetRendererID() const override;

	private:
		uint32_t m_RendererID;
	};

	// Index Buffer ----------------

	class OpenGLIndexBuffer : public IndexBuffer {
	public:
		OpenGLIndexBuffer();
		virtual ~OpenGLIndexBuffer() override;

		virtual void Bind() const override;
		virtual void UnBind() const override;

		virtual void SetData(const void* data, uint32_t count, BufferUsage usage) const override;

		virtual uint32_t GetRendererID() const override;

	private:
		uint32_t m_RendererID;
	};

}