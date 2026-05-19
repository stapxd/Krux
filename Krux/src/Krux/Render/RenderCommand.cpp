#include "krxpch.h"
#include "RenderCommand.h"

namespace Krux {

	Ref<RenderAPI> RenderCommand::s_API = nullptr;

	void RenderCommand::Init()
	{
		s_API = RenderAPI::Create();
	}

	void RenderCommand::Clear()
	{
		s_API->Clear();
	}

	void RenderCommand::ClearColor(glm::vec4 color)
	{
		s_API->ClearColor(color);
	}

	void RenderCommand::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
	{
		s_API->SetViewport(x, y, width, height);
	}

	void RenderCommand::DrawIndexed(Ref<VertexArray> vao, uint32_t indexCount /*= 0*/)
	{
		s_API->DrawIndexed(vao, indexCount);
	}

}
