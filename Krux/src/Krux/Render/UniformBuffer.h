#pragma once

#include "Krux/Core/Ref.h"

#include "Krux/Render/Buffer.h"

namespace Krux {

	class UniformBuffer : public RefCounted {
	public:
		virtual ~UniformBuffer() = default;

		virtual void SetData(const void* data, uint32_t size, uint32_t offset = 0) = 0;

		virtual uint32_t GetRendererID() const = 0;

		static Ref<UniformBuffer> Create(uint32_t size, uint32_t binding, BufferUsage usage = BufferUsage::StaticDraw);
	};

}