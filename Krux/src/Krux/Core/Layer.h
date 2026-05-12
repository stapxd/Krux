#pragma once

#include "Krux/Events/Event.h"
#include "Time.h"

namespace Krux {

	class Layer {
	public:
		Layer(const std::string& name = "Layer")
			: m_Name(name)
		{}

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate(Time time) {}
		virtual void OnEvent(Event& e) {}
		virtual void OnImGuiRender() {}

	private:
		std::string m_Name;
	};

}