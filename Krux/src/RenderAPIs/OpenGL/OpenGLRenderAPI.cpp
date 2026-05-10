#include "krxpch.h"
#include "OpenGLRenderAPI.h"

#include "Krux/Render/VertexArray.h"

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

	void OpenGLRenderAPI::DrawIndexed(Ref<VertexArray> vao, uint32_t indexCount /*= 0*/)
	{
		vao->Bind();
		glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
		vao->UnBind();
	}

}
