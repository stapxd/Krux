#pragma once

#include <string>

namespace Krux {

	struct WindowSpecification {
		std::string Name = "Window";
		int Width = 1600;
		int Height = 900;

		bool IsVSync = false;
	};

	class Window
	{
	public:
		Window(WindowSpecification windowSpec);
		virtual ~Window() = default;

		const std::string& GetName() { return m_Specification.Name; }

		inline int GetWidth()  const { return m_Specification.Width;  }
		inline int GetHeight() const { return m_Specification.Height; }

		bool GetIsVSync() { return m_Specification.IsVSync; }
		virtual void SetVSync(bool value) { m_Specification.IsVSync = value; }

		virtual void Initialize() = 0;
		virtual void OnUpdate() = 0;

	protected:
		WindowSpecification m_Specification;
	};

	Window* CreateApplicationWindow();
}

