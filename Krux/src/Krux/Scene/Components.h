#pragma once

#include "Krux/Core/Core.h"

#include "Krux/Render/Assets/AssetManager.h"

#include "Krux/Core/UUID.h"

#include <iostream>
#include <tuple> 

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>

#define REGISTER_NAME(name) static const char* GetName() { return #name; }

namespace Krux {

	struct IDComponent {
		UUID64 ID;

		IDComponent() = default;
		IDComponent(uint64_t id)
			: ID(id)
		{}

		REGISTER_CLASS_NAME(IDComponent)
		REGISTER_NAME(ID Component)
	};

	struct TagComponent {
		std::string Title = "Untagged";

		TagComponent(const std::string& title = "Untagged")
			: Title(title)
		{}

		REGISTER_CLASS_NAME(TagComponent)
		REGISTER_NAME(Tag Component)
	};

	struct NameComponent {
		std::string Text = "Empty entity";

		NameComponent(const std::string& name = "Empty entity")
			: Text(name)
		{}

		REGISTER_CLASS_NAME(NameComponent)
		REGISTER_NAME(Name Component)
	};


	struct TransformComponent {
		glm::vec3 LocalPosition = glm::vec3(0.0f);
		glm::vec3 Rotation		= glm::vec3(0.0f);
		glm::vec3 Scale			= glm::vec3(1.0f);

		glm::vec3 WorldPosition = glm::vec3(0.0f);

		TransformComponent(glm::vec3 position = glm::vec3(0.0f), glm::vec3 rotation = glm::vec3(0.0f), glm::vec3 scale = glm::vec3(1.0f))
			: LocalPosition(position), Rotation(rotation), Scale(scale)
		{}

		glm::mat4 GetTransform() const
		{
			glm::mat4 rotation = glm::toMat4(glm::quat(Rotation));

			return glm::translate(glm::mat4(1.0f), WorldPosition)
				* rotation
				* glm::scale(glm::mat4(1.0f), Scale);
		}

		REGISTER_CLASS_NAME(TransformComponent)
		REGISTER_NAME(Transform Component)
	};

	struct SpriteRendererComponent {
		glm::vec4 Color = glm::vec4(1.0f);
		AssetHandle TextureHandle = AssetHandle();
		float TilingFactor = 1.0f;

		SpriteRendererComponent(glm::vec4 color = glm::vec4(1.0f), AssetHandle textureHandle = AssetHandle(), float tilingFactor = 1.0f)
			: Color(color), TextureHandle(textureHandle), TilingFactor(tilingFactor)
		{}

		REGISTER_CLASS_NAME(SpriteRendererComponent)
		REGISTER_NAME(Sprite Renderer Component)
	};

	struct CircleRendererComponent {
		glm::vec4 Color = glm::vec4(1.0f);
		float Radius = 1.0f;
		float Thickness = 1.0f;
		float Fade = 0.005f;

		CircleRendererComponent(glm::vec4 color = glm::vec4(1.0f), float radius = 1.0f, float thickness = 1.0f, float fade = 0.005f)
			: Color(color), Radius(radius), Thickness(thickness), Fade(fade)
		{}

		REGISTER_CLASS_NAME(CircleRendererComponent)
		REGISTER_NAME(Circle Renderer Component)
	};

	using AllComponents = std::tuple<
		IDComponent,
		TagComponent,
		NameComponent,
		TransformComponent,
		SpriteRendererComponent, 
		CircleRendererComponent
	>;

}
