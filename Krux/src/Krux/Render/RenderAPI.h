#pragma once

#include "Krux/Core/Ref.h"

#include <glm/glm.hpp>

namespace Krux {

	enum class RenderAPIType {
		None = 0,
		OpenGL
	};

	class RenderAPI : public RefCounted {
	public:
		virtual void Clear() = 0;
		virtual void ClearColor(glm::vec4 color) = 0;
		virtual void DrawIndexed() = 0;

		static RenderAPIType API() { return m_API; }

		static Ref<RenderAPI> Create();
	private:
		static RenderAPIType m_API;
	};

}