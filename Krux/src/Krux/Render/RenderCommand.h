#pragma once

#include "RenderAPI.h"

namespace Krux {
	class RenderCommand
	{
	public:
		static void Init();

		static void Clear();
		static void ClearColor(glm::vec4 color);

	private:
		static Ref<RenderAPI> m_API;
	};
}

