#pragma once

#include "Krux/Core/Ref.h"

namespace Krux {

	enum class BufferUsage {
		StreamDraw,
		StaticDraw,
		DynamicDraw
	};

	// Vertex Buffer ----------------

	class VertexBuffer : public RefCounted {
	public:
		virtual ~VertexBuffer() = default;

		// Maybe unnecessary
		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;
		// -----------------

		virtual void SetData(const void* data, uint32_t size, BufferUsage usage) const = 0;
		virtual void SetSubData(const void* data, uint32_t size, uint32_t offset) const = 0;

		virtual uint32_t GetRendererID() const = 0;

		static Ref<VertexBuffer> Create();
	};

	// Index Buffer ----------------

	class IndexBuffer : public RefCounted {
	public:
		virtual ~IndexBuffer() = default;

		// Maybe unnecessary
		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;
		// -----------------

		virtual void SetData(const void* data, uint32_t count, BufferUsage usage) = 0;

		virtual uint32_t GetRendererID() const = 0;
		uint32_t GetCount() const { return m_Count; }

		static Ref<IndexBuffer> Create();
	protected:
		uint32_t m_Count = 0;
	};

}