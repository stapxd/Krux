#pragma once

#include "Krux/Core/Ref.h"

namespace Krux {

	enum class RenderAPIType {
		None = 0,
		OpenGL
	};

	class RenderAPI : public RefCounted {
	public:
		virtual void DrawIndexed() = 0;

		static RenderAPIType API() { return m_API; }

		static Ref<RenderAPI> Create();
	private:
		static RenderAPIType m_API;
	};

}