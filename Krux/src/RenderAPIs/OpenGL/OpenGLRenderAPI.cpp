#include "krxpch.h"
#include "OpenGLRenderAPI.h"

#include <glad/glad.h>

namespace Krux {

	void OpenGLRenderAPI::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void OpenGLRenderAPI::ClearColor(glm::vec4 color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
	}

	void OpenGLRenderAPI::DrawIndexed()
	{
	}

}
