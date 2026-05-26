#pragma once

#include "Camera.h"

namespace Krux {

	class EditorCameraController;

	class EditorCamera : public Camera {
	public:

		EditorCamera(uint32_t width, uint32_t height);

		void UpdateMouseOffset(float xpos, float ypos);

		virtual void UpdateProjection() override;
		virtual void UpdateView() override;
		virtual glm::mat4 GetProjectionView() const override;

		glm::vec3 Forward() { return m_CameraForward; }
		glm::vec3 Up() { return m_CameraUp; }

	private:
		float m_Near = 0.1f;
		float m_Far = 1000.0f;

		float m_FOV = 60.0f;

		float m_LastX = 0.0f;
		float m_LastY = 0.0f;
		float m_Yaw = -90.0f;
		float m_Pitch = 0.0f;

		glm::vec3 m_Up = glm::vec3(0.0f, 1.0f, 0.0f);
		glm::vec3 m_CameraUp = m_Up;
		glm::vec3 m_CameraForward = m_Position + glm::vec3(0.0f, 0.0f, -1.0f);	

		friend EditorCameraController;
	};

}