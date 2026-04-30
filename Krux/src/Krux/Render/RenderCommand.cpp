#include "krxpch.h"
#include "RenderCommand.h"

namespace Krux {

	void RenderCommand::Init()
	{
		m_API = RenderAPI::Create();
	}

}
