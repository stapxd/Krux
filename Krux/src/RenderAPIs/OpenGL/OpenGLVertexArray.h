#pragma once

#include "Krux/Render/VertexArray.h"

namespace Krux {

	class OpenGLVertexArray : public VertexArray {
	public:
		OpenGLVertexArray();
		virtual ~OpenGLVertexArray() override;

		virtual void Bind() const override;
		virtual void UnBind() const override;

		virtual void AttachVertexBuffer(Ref<VertexBuffer> vbo, const VertexLayout& layout) override;
		virtual void AttachElementBuffer(Ref<IndexBuffer> ebo) override;

		virtual uint32_t GetRendererID() const override { return m_RendererID; };
	private:
		uint32_t m_RendererID;
		uint32_t m_VertexBufferIndex = 0;
	};

}