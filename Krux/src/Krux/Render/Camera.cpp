#include "krxpch.h"
#include "Camera.h"

namespace Krux {

	Camera::Camera(uint32_t width, uint32_t height)
		: m_Width(width), m_Height(height), m_AspectRatio(m_Width / m_Height)
	{
	}

	void Camera::SetViewport(uint32_t width, uint32_t height)
	{
		m_Width = width;
		m_Height = height;

		m_AspectRatio = m_Width / m_Height;
		UpdateProjection();
	}

}
