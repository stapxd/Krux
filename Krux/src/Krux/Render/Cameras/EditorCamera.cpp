#include "krxpch.h"
#include "EditorCamera.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Krux {

    EditorCamera::EditorCamera(uint32_t width, uint32_t height)
        : Camera(width, height)
    {
        m_Position = glm::vec3(0.0f, 0.0f, 5.0f);
        UpdateProjection();
        UpdateView();
    }

    void EditorCamera::UpdateMouseOffset(float xpos, float ypos)
    {
        float xoffset = xpos - m_LastX;
        float yoffset = m_LastY - ypos;
        m_LastX = xpos;
        m_LastY = ypos;

        const float sensitivity = 0.1f;
        xoffset *= sensitivity;
        yoffset *= sensitivity;

        m_Yaw += xoffset;
        m_Pitch += yoffset;

        if (m_Pitch > 89.0f)
            m_Pitch = 89.0f;
        if (m_Pitch < -89.0f)
            m_Pitch = -89.0f;

        glm::vec3 direction;
        direction.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
        direction.y = sin(glm::radians(m_Pitch));
        direction.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
        m_CameraForward = glm::normalize(direction);

        UpdateView();
    }

    void EditorCamera::UpdateProjection()
    {
        m_Projection = glm::perspective(glm::radians(m_FOV), m_AspectRatio, m_Near, m_Far);
    }

    void EditorCamera::UpdateView()
    {
        m_View = glm::lookAt(m_Position, m_Position + m_CameraForward, m_CameraUp);
    }

    glm::mat4 EditorCamera::GetProjectionView() const
    {
        return m_Projection * m_View;
    }

}