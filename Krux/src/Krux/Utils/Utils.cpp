#include "krxpch.h"
#include "Utils.h"

#include "Krux/Render/Buffer.h"

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
    }

}
