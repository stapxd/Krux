#pragma once

#include <glm/glm.hpp>

namespace Krux {

	struct QuadVertex {
		glm::vec3 Position = glm::vec3(0.0f);
		glm::vec4 Color = glm::vec4(1.0f);
		glm::vec2 TextureCoords = glm::vec2(0.0f);
		float TextureIndex = 0.0f;
		float TilingFactor = 1.0f;

		QuadVertex(glm::vec3 pos = glm::vec3(0), glm::vec4 color = glm::vec4(1.0f), glm::vec2 texCoords = glm::vec2(0), float texIndex = 0.0f, float tilingFactor = 1.0f)
			: Position(pos), Color(color), TextureCoords(texCoords), TextureIndex(texIndex), TilingFactor(tilingFactor)
		{}
	};

	struct QuadData {
		glm::vec4 Color = glm::vec4(1.0f);
		AssetHandle Texture;
		float TilingFactor = 1.0f;

		// Transform
		glm::vec3 Position = glm::vec3(0.0f);
		glm::vec2 Size = glm::vec2(1.0f);
		float Rotation = 0.0f;

		// Sorting
		float ZIndex = 0.0f;

		QuadData(glm::vec3 pos, glm::vec2 size, float rotation, AssetHandle texture, float tilingFactor, glm::vec4 color, float zIndex)
			: Position(pos), Size(size), Rotation(rotation), Texture(texture), TilingFactor(tilingFactor), Color(color), ZIndex(zIndex)
		{}
	};


}