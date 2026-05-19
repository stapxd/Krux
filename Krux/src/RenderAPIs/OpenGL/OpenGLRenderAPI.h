#pragma once

#include "Krux/Render/RenderAPI.h"

namespace Krux {

	class OpenGLRenderAPI : public RenderAPI {
	public:
		virtual void Clear() override;
		virtual void ClearColor(glm::vec4 color) override;
		virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;

		virtual void DrawIndexed(Ref<VertexArray> vao, uint32_t indexCount = 0) override;
	};

}