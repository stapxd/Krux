#pragma once

#include "Krux/Core/Ref.h"

#include "Buffer.h"
#include "Krux/Render/VertexLayout.h"

namespace Krux {

	class VertexArray : public RefCounted {
	public:
		virtual ~VertexArray() = default;

		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;

		virtual void AttachVertexBuffer(Ref<VertexBuffer> vbo, const VertexLayout& layout) = 0;
		virtual void AttachElementBuffer(Ref<IndexBuffer> ebo) = 0;

		virtual uint32_t GetRendererID() const = 0;

		static Ref<VertexArray> Create();
	};

}