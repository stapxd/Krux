#pragma once

#include "Krux/Core/Ref.h"
#include "Krux/Render/RenderAPI.h"

struct GLFWwindow;

namespace Krux {
	
	class RenderContext : public RefCounted {
	public:
		virtual bool Init() = 0;
		virtual void SwapBuffers() = 0;

		static Ref<RenderContext> Create(RenderAPIType type);

	protected:
		GLFWwindow* m_Window = nullptr;
	};

}