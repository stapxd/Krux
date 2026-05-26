#include "krxpch.h"
#include "OrthographicCameraController.h"

#include "Krux/Core/Input.h"

#include <glm/glm.hpp>

namespace Krux {

	OrthographicCameraController::OrthographicCameraController(OrthographicCamera& camera)
		: m_Camera(camera)
	{
	}

	void OrthographicCameraController::AddZoom(float value)
	{
		float newZoom = m_Camera.GetZoom() + value * 0.5f;
		m_Camera.SetZoom(newZoom);
	}

	void OrthographicCameraController::OnUpdate(Time time)
	{
		glm::vec2 direction(0.0f);

		if (Input::IsKeyPressed(Key::W)) {
			direction.y =  1.0f;
		}
		else if (Input::IsKeyPressed(Key::S)) {
			direction.y = -1.0f;
		}

		if (Input::IsKeyPressed(Key::A)) {
			direction.x = -1.0f;
		}
		else if (Input::IsKeyPressed(Key::D)) {
			direction.x =  1.0f;
		}

		m_Camera.Move((glm::vec3(direction, 0.0f) * m_CameraSpeed * m_Camera.GetZoom()) * time.DeltaTime());
	}

}