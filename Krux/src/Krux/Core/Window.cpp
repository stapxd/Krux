#include "krxpch.h"
#include "Window.h"

#include "System/Windows/WindowsWindow.h"

namespace Krux {

	Window::Window(WindowSpecification windowSpec)
		: m_Specification(windowSpec)
	{
	}

	Window* CreateApplicationWindow(WindowSpecification windowSpec)
	{
	#if KRX_SYS_WINDOWS
		return new WindowsWindow(windowSpec);
	#endif
	}

}
