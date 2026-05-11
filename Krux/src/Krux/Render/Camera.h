#pragma once

#include <glm/glm.hpp>

namespace Krux {

	class Camera {
	public:
		virtual void UpdateView() = 0;
		virtual void UpdateProjection() = 0;
		virtual glm::mat4 GetProjectionView() const = 0;

		void SetPosition(glm::vec3 position) { m_Position = position; }
		void Move(glm::vec3 direction) { m_Position += direction; }
		glm::vec3 GetPosition() { return m_Position; }

	protected:
		glm::vec3 m_Position = glm::vec3(0);

		glm::mat4 m_View = glm::mat4(1.0f);
		glm::mat4 m_Projection = glm::mat4(1.0f);
	};

}