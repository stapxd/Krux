#pragma once

#include "Asset.h"

namespace Krux {

	enum class TextureFilter {
		Linear,
		Nearest
	};

	enum class TextureWrap {
		ClampToEdge,
		ClampToBorder,
		Repeat,
		MirroredRepeat,
		MirrorClampToEdge
	};

	enum class TextureInternalFormat {
		None = 0,
		R8,
		RGB8,
		RGBA8
	};

	struct TextureSpecification {
		uint32_t Width = 1;
		uint32_t Height = 1;

		TextureFilter MinFilter = TextureFilter::Linear;
		TextureFilter MagFilter = TextureFilter::Linear;

		TextureWrap WrapS = TextureWrap::ClampToEdge;
		TextureWrap WrapT = TextureWrap::ClampToEdge;
		TextureWrap WrapR = TextureWrap::ClampToEdge;

		TextureInternalFormat InternalFormat = TextureInternalFormat::RGBA8;

		/*TextureSpecification(TextureFilter min = TextureFilter::Linear, TextureFilter mag = TextureFilter::Linear, TextureWrap wrapS = TextureWrap::ClampToEdge,
			TextureWrap wrapT = TextureWrap::ClampToEdge, TextureWrap wrapR = TextureWrap::ClampToEdge)
			: MinFilter(min), MagFilter(mag), WrapS(wrapS), WrapT(wrapT), WrapR(wrapR)
		{}*/
	};

	class Texture2D : public Asset {
	public:
		static Ref<Texture2D> Create(const TextureSpecification& spec = {});
		static Ref<Texture2D> Create(const std::filesystem::path& path, const TextureSpecification& spec = {});

		virtual void Bind(uint8_t slot = 0) = 0;

		virtual void SetData(const void* data, uint32_t size) = 0;

		virtual uint32_t GetRendererID() const = 0;

		uint32_t GetWidth() { return m_Specification.Width; }
		uint32_t GetHeight() { return m_Specification.Height; }

	protected:
		TextureSpecification m_Specification;
	};

}