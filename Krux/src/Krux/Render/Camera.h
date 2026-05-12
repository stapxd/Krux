#pragma once

#include <glm/glm.hpp>

namespace Krux {

	class Camera {
	public:
		Camera(uint32_t width, uint32_t height);

		virtual void UpdateView() = 0;
		virtual void UpdateProjection() = 0;
		virtual glm::mat4 GetProjectionView() const = 0;

		void SetViewport(uint32_t width, uint32_t height);

		void SetPosition(glm::vec3 position) { m_Position = position; }
		void Move(glm::vec3 direction) { m_Position += direction; UpdateView(); }
		glm::vec3 GetPosition() { return m_Position; }

	protected:
		float m_Width = 0.0f;
		float m_Height = 0.0f;
		float m_AspectRatio = 0.0f;

		glm::vec3 m_Position = glm::vec3(0);

		glm::mat4 m_View = glm::mat4(1.0f);
		glm::mat4 m_Projection = glm::mat4(1.0f);
	};

}