#pragma once

#include "Krux/Core/Time.h"

#include "EditorCamera.h"

namespace Krux {

	class EditorCameraController {
	public:
		EditorCameraController(EditorCamera& camera);

		void MoveForward(float direction);
		void OnUpdate(Time time, bool viewportHovered);

	private:
		float m_CameraSpeed = 10.0f;
		EditorCamera& m_Camera;

		bool m_FirstMouse = true;
		float m_LastX = 0.0f;
		float m_LastY = 0.0f;
	};

}