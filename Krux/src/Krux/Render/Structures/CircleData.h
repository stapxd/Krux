#pragma once

#include <glm/glm.hpp>

namespace Krux {

	struct CircleVertex {
		glm::vec3 Position = glm::vec3(0.0f);
		glm::vec4 Color = glm::vec4(1.0f);
		glm::vec2 LocalSpaceCoord = glm::vec2(0.0f);
		float Thickness = 1.0f;
		float Fade = 0.005f;

		int EntityID = -1;

		CircleVertex(glm::vec3 pos = glm::vec3(0), glm::vec4 color = glm::vec4(1.0f), glm::vec2 localSpaceCoord = glm::vec2(0), float thickness = 1.0f, float fade = 0.005f, int entityID = -1)
			: Position(pos), Color(color), LocalSpaceCoord(localSpaceCoord), Thickness(thickness), Fade(fade), EntityID(entityID)
		{}
	};

	struct CircleData {
		glm::vec4 Color = glm::vec4(1.0f);
		float Thickness = 1.0f;
		float Fade = 0.005f;

		int EntityID = -1;

		// Transform
		glm::vec3 Position = glm::vec3(0.0f);
		float Radius = 1.0f;

		// Sorting
		float ZIndex = 0.0f;

		CircleData(glm::vec3 pos, float radius, glm::vec4 color, float thickness, float fade, float zIndex, int entityID)
			: Position(pos), Radius(radius), Color(color), Thickness(thickness), Fade(fade), ZIndex(zIndex), EntityID(entityID)
		{}
	};

}