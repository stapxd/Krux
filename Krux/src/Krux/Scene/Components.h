#pragma once

#include "Krux/Core/Core.h"

#include "Krux/Render/Assets/AssetManager.h"

#include "Krux/Core/UUID.h"

#include <glm/glm.hpp>

namespace Krux {

	struct IDComponent {
		UUID64 ID;

		IDComponent(uint64_t id)
			: ID(id)
		{}

		REGISTER_CLASS_NAME(IDComponent)
	};

	struct TagComponent {
		std::string Title = "Untagged";

		TagComponent(const std::string& title = "Untagged")
			: Title(title)
		{}

		REGISTER_CLASS_NAME(TagComponent)
	};

	struct NameComponent {
		std::string Text = "Empty entity";

		NameComponent(const std::string& name = "Empty entity")
			: Text(name)
		{}

		REGISTER_CLASS_NAME(NameComponent)
	};


	struct TransformComponent {
		glm::vec3 Position = glm::vec3(0.0f);
		glm::vec3 Rotation = glm::vec3(0.0f);
		glm::vec3 Scale    = glm::vec3(1.0f);

		TransformComponent(glm::vec3 position = glm::vec3(0.0f), glm::vec3 rotation = glm::vec3(0.0f), glm::vec3 scale = glm::vec3(1.0f))
			: Position(position), Rotation(rotation), Scale(scale)
		{}

		REGISTER_CLASS_NAME(TransformComponent)
	};

	struct SpriteRendererComponent {
		glm::vec4 Color = glm::vec4(1.0f);
		AssetHandle TextureHandle = AssetHandle();
		float TilingFactor = 1.0f;

		SpriteRendererComponent(glm::vec4 color = glm::vec4(1.0f), AssetHandle textureHandle = AssetHandle(), float tilingFactor = 1.0f)
			: Color(color), TextureHandle(textureHandle), TilingFactor(tilingFactor)
		{}

		REGISTER_CLASS_NAME(SpriteRendererComponent)
	};

}
