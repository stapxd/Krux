#pragma once

#include "Krux/Render/Buffer.h"
#include "Krux/Render/VertexArray.h"

#include "Krux/Render/Assets/AssetManager.h"

#include <glm/glm.hpp>

#include <vector>

namespace Krux {

	enum class RendererState {
		None = 0,
		BeginFrame,
		BeginBatch
	};

	struct QuadVertex {
		glm::vec3 Position;
		glm::vec4 Color;

		// TODO: add textures

		QuadVertex(glm::vec3 pos = glm::vec3(0), glm::vec4 color = glm::vec4(1.0f))
			: Position(pos), Color(color)
		{}
	};

	struct QuadData {
		glm::vec4 Color = glm::vec4(1.0f);
		AssetHandle Texture;
		uint16_t TilingFactor = 1;

		// Transform
		glm::vec3 Position = glm::vec3(0.0f);
		glm::vec2 Size = glm::vec2(1.0f);
		float Rotation = 0.0f;

		// Sorting
		float ZIndex = 0.0f;

		QuadData(glm::vec3 pos, glm::vec2 size, float rotation, AssetHandle texture, uint16_t tilingFactor, glm::vec4 color, float zIndex)
			: Position(pos), Size(size), Rotation(rotation), Texture(texture), TilingFactor(tilingFactor), Color(color), ZIndex(zIndex)
		{}
	};

	struct RendererData {
		// Statistics
		int DrawCallsCount = 0;
		
		// Batch
		std::vector<QuadData> BatchQuadsToDraw;
		static uint32_t constexpr MaxQuads = 20000;
		static uint32_t constexpr MaxQuadVertices = MaxQuads * 4;
		static uint32_t constexpr MaxQuadIndices  = MaxQuads * 6;

		QuadVertex* QuadVertexBufferBase = nullptr;
		QuadVertex* QuadVertexBufferPtr = nullptr;

		Ref<VertexArray> BatchQuadVAO;
		Ref<VertexBuffer> BatchQuadVBO;
		Ref<IndexBuffer> BatchQuadEBO;
		AssetHandle BatchColorShaderHandle;

		glm::vec4 QuadVertexPositions[4]{};
		uint32_t QuadIndexCount = 0;

		// Quad Draw
		std::vector<QuadData> QuadsToDraw;
		Ref<VertexArray> QuadVAO;
		Ref<VertexBuffer> QuadVBO;
		Ref<IndexBuffer> QuadEBO;

		// TODO: change to shader library
		AssetHandle QuadTextureShaderHandle;

		AssetHandle WhiteTextureHanle;
	};

	class Renderer2D {
	public:
		static void Init();
		static void Shutdown();
		
		static void BeginFrame();
		static void EndFrame();

		static void BeginBatch();
		static void EndBatch();
		
		static void DrawQuad(glm::vec2 position, glm::vec2 size, glm::vec4 color = glm::vec4(1.0f));
		static void DrawQuad(glm::vec3 position, glm::vec2 size, glm::vec4 color = glm::vec4(1.0f));
		static void DrawQuad(glm::vec2 position, glm::vec2 size, AssetHandle texture, uint16_t tilingFactor = 1, glm::vec4 tintColor = glm::vec4(1.0f));
		static void DrawQuad(glm::vec3 position, glm::vec2 size, AssetHandle texture, uint16_t tilingFactor = 1, glm::vec4 tintColor = glm::vec4(1.0f));

		static void DrawRotatedQuad(glm::vec2 position, glm::vec2 size, float angle, glm::vec4 color = glm::vec4(1.0f));
		static void DrawRotatedQuad(glm::vec3 position, glm::vec2 size, float angle, glm::vec4 color = glm::vec4(1.0f));
		static void DrawRotatedQuad(glm::vec2 position, glm::vec2 size, float angle, AssetHandle texture, uint16_t tilingFactor = 1, glm::vec4 tintColor = glm::vec4(1.0f));
		static void DrawRotatedQuad(glm::vec3 position, glm::vec2 size, float angle, AssetHandle texture, uint16_t tilingFactor = 1, glm::vec4 tintColor = glm::vec4(1.0f));

		static int GetDrawCallsCount() { return s_Data.DrawCallsCount; }

	private:
		static void StartBatch();
		static void NextBatch();
		static void Flush();

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