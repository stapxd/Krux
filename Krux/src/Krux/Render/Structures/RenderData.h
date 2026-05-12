#pragma once

#include "Krux/Core/Ref.h"

#include "Buffer.h"
#include "VertexArray.h"
#include "UniformBuffer.h"

#include "CircleData.h"
#include "QuadData.h"

namespace Krux {

	struct RendererData {
		// Statistics
		int DrawCallsCount = 0;

		// Batch
		static uint32_t constexpr MaxQuads = 20000;
		static uint32_t constexpr MaxQuadVertices = MaxQuads * 4;
		static uint32_t constexpr MaxQuadIndices = MaxQuads * 6;

		// Quad
		std::vector<QuadData> BatchQuadsToDraw;
		QuadVertex* QuadVertexBufferBase = nullptr;
		QuadVertex* QuadVertexBufferPtr = nullptr;

		Ref<VertexArray> BatchQuadVAO;
		Ref<VertexBuffer> BatchQuadVBO;
		Ref<IndexBuffer> BatchQuadEBO;
		AssetHandle BatchQuadShaderHandle;

		glm::vec4 QuadVertexPositions[4]{};
		glm::vec2 QuadTexCoords[4]{};
		uint32_t QuadIndexCount = 0;

		// Circle
		std::vector<CircleData> BatchCirclesToDraw;
		CircleVertex* CircleVertexBufferBase = nullptr;
		CircleVertex* CircleVertexBufferPtr = nullptr;

		Ref<VertexArray> BatchCircleVAO;
		Ref<VertexBuffer> BatchCircleVBO;
		AssetHandle BatchCircleShaderHandle;
		uint32_t CircleIndexCount = 0;

		uint32_t MaxTextureSlots = 32;
		uint32_t TextureIndex = 1;
		std::unordered_map<uint32_t, AssetHandle> TextureSlots;
		int32_t Samplers[32]{};

		// Quad Draw
		std::vector<QuadData> QuadsToDraw;
		Ref<VertexArray> QuadVAO;
		Ref<VertexBuffer> QuadVBO;
		Ref<IndexBuffer> QuadEBO;

		// Circle Draw
		std::vector<CircleData> CirclesToDraw;
		Ref<VertexArray> CircleVAO;
		Ref<VertexBuffer> CircleVBO;

		// TODO: change to shader library
		AssetHandle QuadTextureShaderHandle;
		AssetHandle CircleShaderHandle;

		// Textures
		AssetHandle WhiteTextureHanle;

		// Uniform Data
		struct CameraData {
			glm::mat4 ProjectionView;
		};
		CameraData CameraSettings;
		Ref<UniformBuffer> CameraUniform;
	};

}