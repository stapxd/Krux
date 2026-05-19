#pragma once

#include "Krux/Render/RenderContext.h"

namespace Krux {

	class OpenGLContext : public RenderContext {
	public:
		OpenGLContext(GLFWwindow* window);

		virtual bool Init() override;
		virtual void SwapBuffers() override;
	};

}

