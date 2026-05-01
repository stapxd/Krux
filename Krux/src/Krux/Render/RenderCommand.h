#pragma once

#include "RenderAPI.h"

#include "Krux/Render/VertexArray.h"

namespace Krux {
	class RenderCommand
	{
	public:
		static void Init();

		static void Clear();
		static void ClearColor(glm::vec4 color);

		static void DrawIndexed(Ref<VertexArray> vao, uint32_t indexCount = 0);

	private:
		static Ref<RenderAPI> s_API;
	};
}

