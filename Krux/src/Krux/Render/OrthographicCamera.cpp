#include "krxpch.h"
#include "OrthographicCamera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Krux {

    OrthographicCamera::OrthographicCamera(uint32_t width, uint32_t height)
        : m_Width(width), m_Height(height), m_AspectRatio(m_Width / m_Height)
    {
        UpdateProjection();
        UpdateView();
    }

    void OrthographicCamera::SetViewport(uint32_t width, uint32_t height)
    {
        m_Width = width;
        m_Height = height;

        m_AspectRatio = m_Width / m_Height;
        UpdateProjection();
    }

    void OrthographicCamera::UpdateProjection()
    {
        m_Projection = glm::ortho(-m_AspectRatio * m_Zoom, m_AspectRatio * m_Zoom, -m_Zoom, m_Zoom, 1.0f, -1.0f);
    }

    void OrthographicCamera::UpdateView()
    {
        m_View = glm::translate(m_View, m_Position);
    }

    glm::mat4 OrthographicCamera::GetProjectionView() const
    {
        return m_Projection * m_View;
    }

}