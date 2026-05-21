#pragma once

#include "Krux/Core/Core.h"

#include <glm/glm.hpp>

namespace Krux {


	namespace Components {

		struct ID {
			UUID UUID;

			ID(uint64_t id)
				: UUID(id)
			{}

			REGISTER_CLASS_NAME(ID)
		};

		struct Tag {
			std::string Title = "Untagged";

			Tag(const std::string& title = "Untagged")
				: Title(title)
			{}

			REGISTER_CLASS_NAME(Tag)
		};

		struct Transform {
			glm::vec3 Position = glm::vec3(0.0f);
			glm::vec3 Rotation = glm::vec3(0.0f);
			glm::vec3 Scale    = glm::vec3(1.0f);

			Transform(glm::vec3 position = glm::vec3(0.0f), glm::vec3 rotation = glm::vec3(0.0f), glm::vec3 scale = glm::vec3(1.0f))
				: Position(position), Rotation(rotation), Scale(scale)
			{}

			REGISTER_CLASS_NAME(Transform)
		};

	}

}
