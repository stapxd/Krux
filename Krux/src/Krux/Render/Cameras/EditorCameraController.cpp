#include "krxpch.h"
#include "EditorCameraController.h"

#include "Krux/Core/Log.h"
#include "Krux/Core/Input.h"

namespace Krux {

	EditorCameraController::EditorCameraController(EditorCamera& camera)
		: m_Camera(camera)
	{
	}

	void EditorCameraController::OnUpdate(Time time, bool viewportHovered)
	{
		if (Input::IsMouseButtonPressed(Mouse::BUTTON_LEFT)) {
			Input::SetCursorInputMode(CursorInputMode::NORMAL);
			m_FirstMouse = true;
		}
		else if (Input::IsMouseButtonPressed(Mouse::BUTTON_RIGHT)) {

			if (m_FirstMouse && !viewportHovered)
				return;

			Input::SetCursorInputMode(CursorInputMode::DISABLED);
			double x, y;
			Input::GetMousePosition(x, y);

			if (m_FirstMouse)
			{
				m_Camera.m_LastX = (float)x;
				m_Camera.m_LastY = (float)y;
				m_FirstMouse = false;
			}

			//KRX_CORE_TRACE("MOUSE POS: {} : {}", x, y);
			m_Camera.UpdateMouseOffset((float)x, (float)y);

			glm::vec3 forward = m_Camera.Forward();
			glm::vec3 right = glm::normalize(glm::cross(forward, glm::vec3(0.0f, 1.0f, 0.0f)));
			glm::vec3 up = m_Camera.Up();

			glm::vec3 moveDir(0.0f);

			if (Input::IsKeyPressed(Key::W))
				moveDir += forward;
			if (Input::IsKeyPressed(Key::S))
				moveDir -= forward;

			if (Input::IsKeyPressed(Key::D))
				moveDir += right;
			if (Input::IsKeyPressed(Key::A))
				moveDir -= right;

			if (Input::IsKeyPressed(Key::SPACE))
				moveDir += up;
			if (Input::IsKeyPressed(Key::LEFT_SHIFT))
				moveDir -= up;

			if (glm::dot(moveDir, moveDir) > 0.0005f) {
				moveDir = glm::normalize(moveDir);
				m_Camera.Move(moveDir * m_CameraSpeed * time.DeltaTime());
			}
		}
		else if (Input::IsMouseButtonPressed(Mouse::BUTTON_MIDDLE)) {

			if (m_FirstMouse && !viewportHovered)
				return;

			glm::vec3 cameraRight = glm::normalize(glm::cross(m_Camera.Forward(), m_Camera.Up()));

			double x, y;
			Input::GetMousePosition(x, y);

			if (m_FirstMouse)
			{
				m_LastX = (float)x;
				m_LastY = (float)y;
				m_FirstMouse = false;
			}

			float xoffset = (float)x - m_LastX;
			float yoffset = m_LastY - (float)y;
			m_LastX = (float)x;
			m_LastY = (float)y;

			glm::vec3 direction = -(cameraRight * xoffset + m_Camera.Up() * yoffset);

			if (glm::dot(direction, direction) > 0.0005f)
				m_Camera.Move((glm::normalize(direction) * m_CameraSpeed * 2.5f) * time.DeltaTime());
		}
		else {
			Input::SetCursorInputMode(CursorInputMode::NORMAL);
			m_FirstMouse = true;
		}
	}

	void EditorCameraController::MoveForward(float direction) {
		// Fix with rotation
		glm::vec3 forward = glm::normalize(m_Camera.Forward() * direction);
		m_Camera.Move(forward * m_CameraSpeed * 0.5f);
	}

}