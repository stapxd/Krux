#pragma once

#include "krxpch.h"

namespace Krux {

	struct ApplicationSpecification {
		std::string Name = "Krux Application";
		int Width = 1600;
		int Height = 900;
	};

	class Application
	{
	public:
		Application(ApplicationSpecification specification);
		virtual ~Application();

		const ApplicationSpecification& GetSpecification() const { return m_Specification; }
		// GetWindow()

		void Run();

		static Application* Instance() { return m_Instance; }

	protected:
		inline static Application* m_Instance = nullptr;

		ApplicationSpecification m_Specification;
	};

	Application* Create();
}

