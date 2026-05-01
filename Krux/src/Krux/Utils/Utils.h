#pragma once

#include "Krux/Core/Core.h"

#include "Krux/Render/VertexLayout.h"
#include "Krux/Render/Buffer.h"

#include <glad/glad.h>

namespace Krux {

	namespace Utils {
		int GetSizeOfVertexLayoutType(VertexLayoutType type);

		// OpenGL ---------------
		GLenum GetOpenGLTypeFromVertexLayoutType(VertexLayoutType type);
		GLenum ConvertBufferUsageToOpenGLBufferUsage(BufferUsage usage);
	}

}

