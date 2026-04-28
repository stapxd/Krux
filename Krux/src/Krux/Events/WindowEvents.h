#pragma once

#include "Event.h"

namespace Krux {

	class WindowCloseEvent : public Event {
	public:
		WindowCloseEvent() {}

		EVENT_SET_TYPE(WindowClose);
	};

	class WindowResizeEvent : public Event {
	public:
		WindowResizeEvent(int width, int height) 
			: m_Width(width), m_Height(height)
		{}

		EVENT_SET_TYPE(WindowResize);

		int GetWidth() const { return m_Width; }
		int GetHeight() const { return m_Height; }

	private:
		int m_Width = 0;
		int m_Height = 0;
	};

	class WindowMovedEvent : public Event {
	public:
		WindowMovedEvent(double xpos, double ypos)
			: m_XPos(xpos), m_YPos(ypos)
		{}

		EVENT_SET_TYPE(MouseMoved);

		double GetXPos() const { return m_XPos; }
		double GetYPos() const { return m_YPos; }

	private:
		double m_XPos;
		double m_YPos;
	};

}