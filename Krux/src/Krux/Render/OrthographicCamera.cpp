#include "krxpch.h"
#include "OrthographicCamera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Krux {

    OrthographicCamera::OrthographicCamera(uint32_t width, uint32_t height)
        : Camera(width, height)
    {
        UpdateProjection();
        UpdateView();
    }

    void OrthographicCamera::SetZoom(float value)
    {
        m_Zoom = value;
        m_Zoom = glm::clamp(m_Zoom, 1.0f, 10.0f);

        UpdateProjection();
    }

    void OrthographicCamera::UpdateProjection()
    {
        m_Projection = glm::ortho(-m_AspectRatio * m_Zoom, m_AspectRatio * m_Zoom, -m_Zoom, m_Zoom, 1.0f, -1.0f);
    }

    void OrthographicCamera::UpdateView()
    {
        m_View = glm::translate(glm::mat4(1.0f), -m_Position);
    }

    glm::mat4 OrthographicCamera::GetProjectionView() const
    {
        return m_Projection * m_View;
    }

}