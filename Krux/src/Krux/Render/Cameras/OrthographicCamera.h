#pragma once

#include "Camera.h"

namespace Krux {

	class OrthographicCamera : public Camera {
	public:
		OrthographicCamera(uint32_t width, uint32_t height);

		void SetZoom(float value);
		float GetZoom() const { return m_Zoom; }

		virtual void UpdateProjection() override;
		virtual void UpdateView() override;
		virtual glm::mat4 GetProjectionView() const override;

	private:
		float m_Zoom = 1.0f;
	};

}