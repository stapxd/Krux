#include "krxpch.h"
#include "RenderCommand.h"

namespace Krux {

	Ref<RenderAPI> RenderCommand::m_API = nullptr;

	void RenderCommand::Init()
	{
		m_API = RenderAPI::Create();
	}

	void RenderCommand::Clear()
	{
		m_API->Clear();
	}

	void RenderCommand::ClearColor(glm::vec4 color)
	{
		m_API->ClearColor(color);
	}

}
