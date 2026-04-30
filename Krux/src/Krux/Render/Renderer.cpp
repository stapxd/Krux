#include "krxpch.h"
#include "Renderer.h"

#include "RenderCommand.h"

namespace Krux {

	void Renderer::Init()
	{
		RenderCommand::Init();

		RenderCommand::ClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
	}

	void Renderer::Clear()
	{
		RenderCommand::Clear();
	}

	void Renderer::ClearColor(glm::vec4 color)
	{
		RenderCommand::ClearColor(color);
	}

	void Renderer::ClearColor(float r, float g, float b, float a /*= 1.0f*/)
	{
		ClearColor(glm::vec4(r, g, b, a));
	}

}