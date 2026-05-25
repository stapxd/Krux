#include "krxpch.h"
#include "Utils.h"

#include "Krux/Render/Buffer.h"

#include <array>

namespace Krux {

    namespace Utils {
        int GetSizeOfVertexLayoutType(VertexLayoutType type) {
			switch (type)
			{
			case Krux::VertexLayoutType::Float:
			case Krux::VertexLayoutType::Int:
			case Krux::VertexLayoutType::UnsignedInt:
				return 4;
			}

			KRX_CORE_ASSERT(false, "Invalid VertexLayoutType!");
			return -1;
		}

        GLenum GetOpenGLTypeFromVertexLayoutType(VertexLayoutType type) {
			switch (type)
			{
			case Krux::VertexLayoutType::Float:
				return GL_FLOAT;
			case Krux::VertexLayoutType::Int:
				return GL_INT;
			case Krux::VertexLayoutType::UnsignedInt:
				return GL_UNSIGNED_INT;
			}

			KRX_CORE_ASSERT(false, "Invalid VertexLayoutType!");
			return 0;
		}

		GLenum ConvertBufferUsageToOpenGLBufferUsage(BufferUsage usage) {
			switch (usage)
			{
			case Krux::BufferUsage::StreamDraw:
				return GL_STREAM_DRAW;
			case Krux::BufferUsage::StaticDraw:
				return GL_STATIC_DRAW;
			case Krux::BufferUsage::DynamicDraw:
				return GL_DYNAMIC_DRAW;
			}

			KRX_CORE_ASSERT(false, "Invalid BufferUsage!");
			return 0;
		}

		// Texture
		GLint TextureFilterToOpenGLParam(TextureFilter filter)
		{
			switch (filter)
			{
			case Krux::TextureFilter::Linear:
				return GL_LINEAR;
			case Krux::TextureFilter::Nearest:
				return GL_NEAREST;
			}
			
			KRX_CORE_ASSERT(false, "Invalid TextureFilter!");
			return 0;
		}
		GLint TextureWrapToOpenGLParam(TextureWrap wrap)
		{
			switch (wrap)
			{
			case Krux::TextureWrap::ClampToEdge:
				return GL_CLAMP_TO_EDGE;
			case Krux::TextureWrap::ClampToBorder:
				return GL_CLAMP_TO_BORDER;
			case Krux::TextureWrap::Repeat:
				return GL_REPEAT;
			case Krux::TextureWrap::MirroredRepeat:
				return GL_MIRRORED_REPEAT;
			case Krux::TextureWrap::MirrorClampToEdge:
				return GL_MIRROR_CLAMP_TO_EDGE;
			}

			KRX_CORE_ASSERT(false, "Invalid TextureWrap!");
			return 0;
		}
		GLint TextureInternalFormatToOpenGLFormat(TextureInternalFormat format)
		{
			switch (format)
			{
			case Krux::TextureInternalFormat::R8:
				return GL_R8;
			case Krux::TextureInternalFormat::RGB8:
				return GL_RGB8;
			case Krux::TextureInternalFormat::RGBA8:
				return GL_RGBA8;
			}

			KRX_CORE_ASSERT(false, "Invalid TextureInternalFormat!");
			return 0;
		}

		GLint TexturePixelFormatToOpenGLFormat(TextureInternalFormat format)
		{
			switch (format)
			{
			case Krux::TextureInternalFormat::R8:
				return GL_RED;
			case Krux::TextureInternalFormat::RGB8:
				return GL_RGB;
			case Krux::TextureInternalFormat::RGBA8:
				return GL_RGBA;
			}

			KRX_CORE_ASSERT(false, "Invalid TexturePixelFormat!");
			return 0;
		}

		uint32_t GetTextureInternalFormatBPP(TextureInternalFormat format)
		{
			switch (format)
			{
			case Krux::TextureInternalFormat::R8:
				return 1;
			case Krux::TextureInternalFormat::RGB8:
				return 3;
			case Krux::TextureInternalFormat::RGBA8:
				return 4;
			}

			KRX_CORE_ASSERT(false, "Invalid TexturePixelFormat!");
			return 0;
		}

		// FrameBuffer Attachments
		AttachmentType GetAttachmentType(FrameBufferAttachment attachment)
		{
			switch (attachment)
			{
			case Krux::FrameBufferAttachment::Int32:
			case Krux::FrameBufferAttachment::Int8:
			case Krux::FrameBufferAttachment::RGB8:
			case Krux::FrameBufferAttachment::RGBA8:
				return AttachmentType::Color;
			case Krux::FrameBufferAttachment::Depth24_Stencil8:
				return AttachmentType::Depth;
			}

			KRX_CORE_ASSERT(false, "Invalid FrameBufferAttachment!");
			return AttachmentType::None;
		}
		GLint FrameBufferAttachmentToOpenGLInternalFormat(FrameBufferAttachment attachment)
		{
			switch (attachment)
			{
			case Krux::FrameBufferAttachment::Int32:
				return GL_R32I;
			case Krux::FrameBufferAttachment::Int8:
				return GL_R8I;
			case Krux::FrameBufferAttachment::RGB8:
				return GL_RGB8;
			case Krux::FrameBufferAttachment::RGBA8:
				return GL_RGBA8;
			case Krux::FrameBufferAttachment::Depth24_Stencil8:
				return GL_DEPTH24_STENCIL8;
			}

			KRX_CORE_ASSERT(false, "Invalid FrameBufferAttachment!");
			return 0;
		}

		// File System
		bool IsPathATexture(const std::filesystem::path& path) {
			if (path.empty())
				return false;

			std::array<const char*, 7> textureExtensions{ ".png", ".jpeg", ".jpg", ".bmp", ".pic", ".tga", ".hdr" };

			std::string extStr = path.extension().string();
			const char* extension = extStr.c_str();
			for (auto ext : textureExtensions) {
				if (strcmp(extension, ext) == 0) {
					return true;
				}
			}

			return false;
		}

		bool IsPathAShader(const std::filesystem::path& path) {
			if (path.empty()) 
				return false;

			std::array<const char*, 1> shaderExtensions{ ".glsl" };

			std::string extension = path.extension().string();
			for (auto ext : shaderExtensions)
				if (extension == ext)
					return true;

			return false;
		}

    }

}
