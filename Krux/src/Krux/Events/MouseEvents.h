#pragma once

#include "Event.h"

namespace Krux {

	class MouseButtonPressedEvent : public Event {
	public:
		MouseButtonPressedEvent(int keyCode)
			: m_KeyCode(keyCode)
		{}

		EVENT_SET_TYPE(MouseButtonPressed);
		EVENT_SET_CATEGORY(MouseButtonEvent);

		int GetKey() const { return m_KeyCode; }

	private:
		int m_KeyCode;
	};

	class MouseButtonReleasedEvent : public Event {
	public:
		MouseButtonReleasedEvent(int keyCode)
			: m_KeyCode(keyCode)
		{}

		EVENT_SET_TYPE(MouseButtonReleased);
		EVENT_SET_CATEGORY(MouseButtonEvent);

		int GetKey() const { return m_KeyCode; }

	private:
		int m_KeyCode;
	};

	class MouseScrollEvent : public Event {
	public:
		MouseScrollEvent(double xoffset, double yoffset)
			: m_XOffset(xoffset), m_YOffset(yoffset)
		{}

		EVENT_SET_TYPE(MouseScrolled);
		EVENT_SET_CATEGORY(MouseButtonEvent);

		double GetXOffset() const { return m_XOffset; }
		double GetYOffset() const { return m_YOffset; }

	private:
		double m_XOffset;
		double m_YOffset;
	};

	class MouseMovedEvent : public Event {
	public:
		MouseMovedEvent(double xpos, double ypos)
			: m_XPos(xpos), m_YPos(ypos)
		{}

		EVENT_SET_TYPE(MouseMoved);
		EVENT_SET_CATEGORY(MouseEvent);

		double GetXPos() const { return m_XPos; }
		double GetYPos() const { return m_YPos; }

	private:
		double m_XPos;
		double m_YPos;
	};
}