#pragma once

#include "OrthographicCamera.h"

#include "Krux/Core/Time.h"

// TODO: temp class
namespace Krux {

	class OrthographicCameraController {
	public:
		OrthographicCameraController(OrthographicCamera& camera);

		void AddZoom(float value);
		void OnUpdate(Time time);

	private:
		float m_CameraSpeed = 1.0f;
		OrthographicCamera& m_Camera;
	};
}
