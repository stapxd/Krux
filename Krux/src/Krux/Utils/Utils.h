#pragma once

#include "Krux/Core/Core.h"

#include "Krux/Render/VertexLayout.h"
#include "Krux/Render/Buffer.h"

#include "Krux/Render/Assets/Texture2D.h"
#include "Krux/Render/FrameBuffer.h"

#include <filesystem>
#include <glad/glad.h>

namespace Krux {

	namespace Utils {
		int GetSizeOfVertexLayoutType(VertexLayoutType type);

		// OpenGL ---------------
		GLenum GetOpenGLTypeFromVertexLayoutType(VertexLayoutType type);
		GLenum ConvertBufferUsageToOpenGLBufferUsage(BufferUsage usage);
			
			// Texture
		GLint TextureFilterToOpenGLParam(TextureFilter filter);
		GLint TextureWrapToOpenGLParam(TextureWrap wrap);
		GLint TextureInternalFormatToOpenGLFormat(TextureInternalFormat format);
		GLint TexturePixelFormatToOpenGLFormat(TextureInternalFormat format);
		uint32_t GetTextureInternalFormatBPP(TextureInternalFormat format);

			// FrameBuffer Attachments
		AttachmentType GetAttachmentType(FrameBufferAttachment attachment);
		GLint FrameBufferAttachmentToOpenGLInternalFormat(FrameBufferAttachment attachment);

		// File System
		bool IsPathATexture(const std::filesystem::path& path);
		bool IsPathAShader(const std::filesystem::path& path);
	}

}

