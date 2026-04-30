#pragma once

#include "RenderAPI.h"

namespace Krux {
	class RenderCommand
	{
	public:
		static void Init();
	private:
		static Ref<RenderAPI> m_API;
	};
}

