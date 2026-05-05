#pragma once

#include "Krux/Render/Buffer.h"
#include "Krux/Render/VertexArray.h"
#include "Krux/Render/Assets/Shader.h"
#include "Krux/Render/Assets/AssetManager.h"

#include <glm/glm.hpp>

#include <vector>

namespace Krux {

	enum class RendererState {
		None = 0,
		BeginFrame,
		BeginBatch
	};

	struct QuadData {
		glm::vec3 Position = glm::vec3(0.0f);
		glm::vec2 Size = glm::vec2(1.0f);
		float Rotation = 0.0f;
		glm::vec4 Color = glm::vec4(1.0f);

		// Sorting
		float ZIndex = 0.0f;

		QuadData(glm::vec3 pos, glm::vec2 size, float rotation, glm::vec4 color, float zIndex)
			: Position(pos), Size(size), Rotation(rotation), Color(color), ZIndex(zIndex)
		{}
	};

	struct RendererData {
		std::vector<QuadData> QuadsToDraw;

		// Buffers
		Ref<VertexArray> QuadVAO;
		Ref<VertexBuffer> QuadVBO;
		Ref<IndexBuffer> QuadEBO;

		// TODO: change to shader library
		AssetHandle ColorShaderHandle;
	};

	class Renderer2D {
	public:
		static void Init();
		
		static void BeginFrame();
		static void EndFrame();

		static void BeginBatch();
		static void EndBatch();
		
		static void DrawQuad(glm::vec2 position, glm::vec2 size, glm::vec4 color = glm::vec4(1.0f));
		static void DrawQuad(glm::vec3 position, glm::vec2 size, glm::vec4 color = glm::vec4(1.0f));

		static void DrawRotatedQuad(glm::vec2 position, glm::vec2 size, float angle, glm::vec4 color = glm::vec4(1.0f));
		static void DrawRotatedQuad(glm::vec3 position, glm::vec2 size, float angle, glm::vec4 color = glm::vec4(1.0f));

	private:
		static std::vector<RendererState> s_RendererStateStack;
		static RendererState s_CurrentState;

		static RendererData s_Data;
	};

}

/*

Renderer2D::BeginFrame(); // BeginFrame

Renderer2D::BeginBatch();
Renderer2D::DrawQuad(position, size, color);
Renderer2D::EndBatch();

Renderer2D::DrawQuad(position, size, color);

Renderer2D::EndFrame();

BeginFrame, BeginBatch,

*/