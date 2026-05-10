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
    }

}
