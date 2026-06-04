#include "krxpch.h"
#include "CameraSystem.h"

#include "Krux/Core/Core.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Krux {
	
	void CameraSystem::RecalculateProjection(CameraComponent& camera)
	{
		if (camera.Width <= 0.0f || camera.Height <= 0.0f)
			return;

		float aspect = camera.Width / camera.Height;

		switch (camera.Type)
		{
			case CameraType::Perspective: {
				camera.Projection = glm::perspective(glm::radians(camera.FOV), aspect, camera.PerspectiveNear, camera.PerspectiveFar);
				return;
			}
			case CameraType::Orthographic: {
				camera.Projection = glm::ortho(-aspect * camera.OrthoZoom, aspect * camera.OrthoZoom, -camera.OrthoZoom, camera.OrthoZoom, camera.OrthoNear, camera.OrthoFar);
				return;
			}
		}

		KRX_CORE_ASSERT(false, "Invalid Camera Type!");
	}

}