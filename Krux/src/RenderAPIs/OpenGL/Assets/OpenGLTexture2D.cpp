#include "krxpch.h"
#include "OpenGLTexture2D.h"

#include "Krux/Core/Core.h"

#include "Krux/Utils/Utils.h"

#include <glad/glad.h>
#include <stb/stb_image.h>

namespace Krux {

	OpenGLTexture2D::OpenGLTexture2D(const TextureSpecification& spec)
	{
		m_Specification = spec;
		glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);

		unsigned int white = 0xffffffff;

		glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, Utils::TextureFilterToOpenGLParam(spec.MinFilter));
		glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, Utils::TextureFilterToOpenGLParam(spec.MagFilter));

		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, Utils::TextureWrapToOpenGLParam(spec.WrapS));
		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, Utils::TextureWrapToOpenGLParam(spec.WrapT));
		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_R, Utils::TextureWrapToOpenGLParam(spec.WrapR));

		glTextureStorage2D(m_RendererID, 1, Utils::TextureInternalFormatToOpenGLFormat(m_Specification.InternalFormat), m_Specification.Width, m_Specification.Height);

		glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Specification.Width, m_Specification.Height,
			Utils::TexturePixelFormatToOpenGLFormat(m_Specification.InternalFormat), GL_UNSIGNED_BYTE, &white);

		glGenerateTextureMipmap(m_RendererID);
	}

	OpenGLTexture2D::OpenGLTexture2D(const std::filesystem::path& path, const TextureSpecification& spec)
	{
		m_Specification = spec;

		glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);

		KRX_CORE_ASSERT(Load(path), "Could not load Texture2D!");

		glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, Utils::TextureFilterToOpenGLParam(spec.MinFilter));
		glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, Utils::TextureFilterToOpenGLParam(spec.MagFilter));

		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, Utils::TextureWrapToOpenGLParam(spec.WrapS));
		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, Utils::TextureWrapToOpenGLParam(spec.WrapT));
		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_R, Utils::TextureWrapToOpenGLParam(spec.WrapR));

		glGenerateTextureMipmap(m_RendererID);
	}

	bool OpenGLTexture2D::Load(const std::filesystem::path& path)
	{
		stbi_set_flip_vertically_on_load(1);

		int width, height;
		int channels;
		std::string pathStr = path.string();

		stbi_uc* data = nullptr;
		data = stbi_load(pathStr.c_str(), &width, &height, &channels, 0);

		m_Specification.Width = width;
		m_Specification.Height = height;

		if (data) {
			m_Specification.InternalFormat = TextureInternalFormat::None;

			if (channels == 3) {
				m_Specification.InternalFormat = TextureInternalFormat::RGB8;
			}
			else if (channels == 4) {
				m_Specification.InternalFormat = TextureInternalFormat::RGBA8;
			}

			KRX_CORE_ASSERT((bool)m_Specification.InternalFormat, "Texture2D formats are insupported!");

			glTextureStorage2D(m_RendererID, 1, Utils::TextureInternalFormatToOpenGLFormat(m_Specification.InternalFormat), m_Specification.Width, m_Specification.Height);

			glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Specification.Width, m_Specification.Height, 
				Utils::TexturePixelFormatToOpenGLFormat(m_Specification.InternalFormat), GL_UNSIGNED_BYTE, data);

			stbi_image_free(data);

			return true;
		}
		else {
			return false;
		}
	}

	void OpenGLTexture2D::Bind(uint8_t slot)
	{
		glBindTextureUnit(slot, m_RendererID);
	}

}