#pragma once

#include "Krux/Render/Assets/Texture2D.h"

namespace Krux {

	class OpenGLTexture2D : public Texture2D {
	public:
		OpenGLTexture2D(const TextureSpecification& spec);
		OpenGLTexture2D(const std::filesystem::path& path, const TextureSpecification& spec);

		virtual bool Load(const std::filesystem::path& path) override;

		virtual void Bind(uint8_t slot = 0) override;

		virtual uint32_t GetRendererID() const override { return m_RendererID; }

	private:
		uint32_t m_RendererID;
	};

}