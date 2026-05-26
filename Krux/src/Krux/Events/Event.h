#pragma once

#include "Krux/Core/Core.h"

#include <functional>

namespace Krux {

	enum class EventType {
		None = 0,
		WindowClose, WindowResize, WindowMoved,
		KeyPressed, KeyReleased,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

	enum EventCategoty {
		None = 0,
		WindowEvent = BIT(1),
		KeyEvent = BIT(2),
		MouseEvent = BIT(3),
		MouseButtonEvent = BIT(4),
	};

	#define EVENT_SET_TYPE(type) static EventType GetStaticType() { return EventType::##type; } \
								 virtual EventType GetType() override { return  GetStaticType(); }

	#define EVENT_SET_CATEGORY(category) virtual int GetCategoty() override { return (int)(category); }

	class Event
	{
	public:
		bool IsHandled = false;
	
	public:
		bool IsInCategory(EventCategoty category) { return GetCategoty() & (int)category; }

		virtual EventType GetType() = 0;
		virtual int GetCategoty() = 0;

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

