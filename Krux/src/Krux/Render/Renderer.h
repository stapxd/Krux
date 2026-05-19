#pragma once

#include <glm/glm.hpp>

namespace Krux {

	class Renderer {
	public:
		static void Init();
		static void Shutdown();

		static void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height);
		static void Clear();
		static void ClearColor(glm::vec4 color);
		static void ClearColor(float r, float g, float b, float a = 1.0f);
	};

}