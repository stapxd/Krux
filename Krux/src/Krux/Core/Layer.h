#pragma once

#include "Krux/Events/Event.h"
#include "Time.h"
#include "Ref.h"

namespace Krux {

	class Layer : public RefCounted {
	public:
		Layer(const std::string& name = "Layer")
			: m_Name(name)
		{}

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate(Time time) {}
		virtual void OnRender() {}
		virtual void OnEvent(Event& e) {}
		virtual void OnImGuiRender() {}

	private:
		std::string m_Name;
	};

}