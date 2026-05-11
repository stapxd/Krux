#pragma once

#include "Camera.h"

namespace Krux {

	class OrthographicCamera : public Camera {
	public:
		OrthographicCamera(uint32_t width, uint32_t height);

		void SetViewport(uint32_t width, uint32_t height);

		virtual void UpdateProjection() override;
		virtual void UpdateView() override;
		virtual glm::mat4 GetProjectionView() const override;

	private:
		float m_Width = 0.0f;
		float m_Height = 0.0f;

		float m_Zoom = 1.0f;
		float m_AspectRatio = 0.0f;
	};

}