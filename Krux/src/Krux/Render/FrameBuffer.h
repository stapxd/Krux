#pragma once

#include "Krux/Core/Ref.h"

#include <vector>

namespace Krux {

	enum class AttachmentType {
		None = 0,
		Color,
		Depth
	};

	enum class FrameBufferAttachment {
		None = 0,
		Int32,
		Int8,
		RGB8,
		RGBA8,
		Depth24_Stencil8
	};

	struct FrameBufferSpecification {
		std::vector<FrameBufferAttachment> Attachments;
		uint32_t Width = 0;
		uint32_t Height = 0;
	};

	class FrameBuffer : public RefCounted {
	public:
		virtual ~FrameBuffer() = default;

		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;
		virtual int  ReadPixel(uint32_t attachmentIndex, int posX, int posY) const = 0;
		virtual void ClearAttachment(uint32_t attachmentIndex, void* data) = 0;

		virtual void Resize(uint32_t width, uint32_t height) = 0;
		virtual void Invalidate() = 0;

		virtual uint32_t GetRendererID() const = 0;
		uint32_t GetAttachmentID(size_t index);

		static Ref<FrameBuffer> Create(FrameBufferSpecification spec);

	protected:
		FrameBufferSpecification m_Specification;
		std::vector<uint32_t> m_AttachmentIDs;
	};

}