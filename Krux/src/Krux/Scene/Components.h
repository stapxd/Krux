#pragma once

#include "Krux/Core/Core.h"

#include "Krux/Render/Assets/AssetManager.h"

#include "Krux/Core/UUID.h"

#include <glm/glm.hpp>

namespace Krux {

	namespace Components {

		struct IDComponent {
			UUID64 ID;

			IDComponent(uint64_t id)
				: ID(id)
			{}

			REGISTER_CLASS_NAME(IDComponent)
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

		struct SpriteRenderer {
			glm::vec4 Color = glm::vec4(1.0f);
			AssetHandle TextureHandle = AssetHandle();
			float TilingFactor = 1.0f;

			SpriteRenderer(glm::vec4 color = glm::vec4(1.0f), AssetHandle textureHandle = AssetHandle(), float tilingFactor = 1.0f)
				: Color(color), TextureHandle(textureHandle), TilingFactor(tilingFactor)
			{}

			REGISTER_CLASS_NAME(SpriteRenderer)
		};

	}

}
