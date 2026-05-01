#pragma once

#include "Krux/Render/RenderAPI.h"

namespace Krux {

	class OpenGLRenderAPI : public RenderAPI {
	public:
		virtual void Clear() override;
		virtual void ClearColor(glm::vec4 color) override;
		virtual void DrawIndexed(Ref<VertexArray> vao, uint32_t indexCount = 0) override;
	};

}