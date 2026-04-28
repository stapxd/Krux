#pragma once

#include <functional>

namespace Krux {

	enum class EventType {
		None = 0,
		WindowClose, WindowResize, WindowMoved,
		KeyPressed, KeyReleased,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

	#define EVENT_SET_TYPE(type) static EventType GetStaticType() { return EventType::##type; } \
								 virtual EventType GetType() override { return  GetStaticType(); }

	class Event
	{
	public:
		bool IsHandled = false;
	
	public:
		virtual EventType GetType() = 0;

	protected:
		static EventType m_Type;
	};

	class EventDispatcher {
	public:
		template<typename T>
		using EventFn = std::function<bool(T&)>;
	public:
		EventDispatcher(Event& e)
			: m_Event(e)
		{}

		template<typename T>
		bool Dispatch(EventFn<T> fn) {
			if (m_Event.GetType() == T::GetStaticType()) {
				m_Event.IsHandled = fn(*(T*)&m_Event);
				return true;
			}
			return false;
		}
	private:
		Event& m_Event;
	};
}

