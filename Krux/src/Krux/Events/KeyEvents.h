#pragma once

#include "Event.h"

namespace Krux {
	
	class KeyPressedEvent : public Event {
	public:
		KeyPressedEvent(int keyCode, int isRepeated)
			: m_KeyCode(keyCode), m_IsRepeated(isRepeated)
		{}

		EVENT_SET_TYPE(KeyPressed);
		EVENT_SET_CATEGORY(KeyEvent);

		int GetKey() const { return m_KeyCode; }
		int IsRepeated() const { return m_IsRepeated; }

	private:
		int m_KeyCode;
		bool m_IsRepeated;
	};

	class KeyReleasedEvent : public Event {
	public:
		KeyReleasedEvent(int keyCode)
			: m_KeyCode(keyCode)
		{}

		EVENT_SET_TYPE(KeyReleased);
		EVENT_SET_CATEGORY(KeyEvent);

		int GetKey() const { return m_KeyCode; }

	private:
		int m_KeyCode;
	};
}