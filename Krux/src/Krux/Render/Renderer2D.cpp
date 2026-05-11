#include "krxpch.h"
#include "Renderer2D.h"

#include "Krux/Core/Core.h"

#include "Assets/AssetManager.h"
#include "Krux/Render/Assets/Shader.h"
#include "Krux/Render/Assets/Texture2D.h"

#include "RenderCommand.h"

#include <glm/gtc/matrix_transform.hpp>

#include <cassert>

namespace Krux {
	
	std::vector<RendererState> Renderer2D::s_RendererStateStack;
	RendererState Renderer2D::s_CurrentState = RendererState::None;

	RendererData Renderer2D::s_Data;

	void Renderer2D::Init()
	{
		// Batch draw
		{
			KRX_CORE_ASSERT(s_Data.MaxQuads != 0, "Batch Max Quads should not be 0!");

			s_Data.QuadVertexPositions[0] = { -0.5f, -0.5f, 0.0f, 1.0f };
			s_Data.QuadVertexPositions[1] = {  0.5f, -0.5f, 0.0f, 1.0f };
			s_Data.QuadVertexPositions[2] = {  0.5f,  0.5f, 0.0f, 1.0f };
			s_Data.QuadVertexPositions[3] = { -0.5f,  0.5f, 0.0f, 1.0f };

			s_Data.BatchColorShaderHandle = AssetManager::Load<Shader>("assets/builtin/shaders/batchColor.glsl");

			s_Data.BatchQuadVAO = VertexArray::Create();

			s_Data.BatchQuadVBO = VertexBuffer::Create();
			s_Data.BatchQuadVBO->SetData(nullptr, s_Data.MaxQuadVertices * sizeof(QuadVertex), BufferUsage::DynamicDraw);

			VertexLayout batchLayout = {
				{ 3, VertexLayoutType::Float, false },
				{ 4, VertexLayoutType::Float, false },
			};

			s_Data.BatchQuadVAO->AttachVertexBuffer(s_Data.BatchQuadVBO, batchLayout);

			s_Data.QuadVertexBufferBase = new QuadVertex[s_Data.MaxQuadVertices];

			uint32_t* quadIndices = new uint32_t[s_Data.MaxQuadIndices];

			uint32_t offset = 0;
			for (uint32_t i = 0; i < s_Data.MaxQuadIndices; i += 6) {
				quadIndices[i + 0] = offset + 0;
				quadIndices[i + 1] = offset + 1;
				quadIndices[i + 2] = offset + 2;

				quadIndices[i + 3] = offset + 2;
				quadIndices[i + 4] = offset + 3;
				quadIndices[i + 5] = offset + 0;
				offset += 4;
			}

			s_Data.BatchQuadEBO = IndexBuffer::Create();
			s_Data.BatchQuadEBO->SetData(quadIndices, s_Data.MaxQuadIndices, BufferUsage::StaticDraw);
			s_Data.BatchQuadVAO->AttachElementBuffer(s_Data.BatchQuadEBO);

			delete[] quadIndices;

		}

		// Regular draw
		{
			s_Data.QuadTextureShaderHandle = AssetManager::Load<Shader>("assets/builtin/shaders/QuadTexture.glsl");

			s_Data.QuadVAO = VertexArray::Create();

			float vertices[4 * 5] = {
				-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
				 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
				 0.5f,  0.5f, 0.0f,	1.0f, 1.0f,
				-0.5f,  0.5f, 0.0f,	0.0f, 1.0f
			};

			s_Data.QuadVBO = VertexBuffer::Create();
			s_Data.QuadVBO->SetData(vertices, sizeof(vertices), BufferUsage::StaticDraw);


			VertexLayout layout = {
				{ 3, VertexLayoutType::Float, false }, // Position
				{ 2, VertexLayoutType::Float, false }  // Texture Coords
			};

			s_Data.QuadVAO->AttachVertexBuffer(s_Data.QuadVBO, layout);

			unsigned int indices[6] = {
				0, 1, 2,
				2, 3, 0
			};

			s_Data.QuadEBO = IndexBuffer::Create();
			s_Data.QuadEBO->SetData(indices, sizeof(indices) / 4, BufferUsage::StaticDraw);

			s_Data.QuadVAO->AttachElementBuffer(s_Data.QuadEBO);
		}

		s_Data.WhiteTextureHanle = AssetManager::CreateMemoryOnlyAsset<Texture2D>();
	}

	void Renderer2D::Shutdown() 
	{
		delete[] s_Data.QuadVertexBufferBase;
	}

	void Renderer2D::BeginFrame()
	{
		s_RendererStateStack.clear();
		s_Data.QuadsToDraw.clear();
		s_Data.DrawCallsCount = 0;

		s_CurrentState = RendererState::BeginFrame;
		s_RendererStateStack.emplace_back(RendererState::BeginFrame);
	}

	void Renderer2D::EndFrame()
	{
		auto it = s_RendererStateStack.begin(); // BeginFrame is the first thing a person calls
		if(it == s_RendererStateStack.end())
			KRX_CORE_ASSERT(false, "Forgot to call Renderer2D::BeginFrame()!");
		KRX_CORE_ASSERT(s_CurrentState == RendererState::BeginFrame, "Renderer2D::EndFrame() : Forgot to close previous section!");

		// Remove Shader and move into Shader Library
		if (s_Data.QuadsToDraw.size() != 0) {
			std::sort(s_Data.QuadsToDraw.begin(), s_Data.QuadsToDraw.end(), [](const QuadData& q1, const QuadData& q2) {
				return q1.ZIndex < q2.ZIndex;
			});

			Ref<Shader> quadTextureShader = AssetManager::GetAsset<Shader>(s_Data.QuadTextureShaderHandle);
			quadTextureShader->Bind();
			for (auto& quad : s_Data.QuadsToDraw) {
				
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), quad.Position) * 
					glm::rotate(glm::mat4(1.0f), glm::radians(quad.Rotation), glm::vec3(0.0f, 0.0f, 1.0f)) *
					glm::scale(glm::mat4(1.0f), glm::vec3(quad.Size, 1.0f));
				quadTextureShader->SetMat4("u_Model", transform);

				quadTextureShader->SetFloat4("u_TintColor", quad.Color.r, quad.Color.g, quad.Color.b, quad.Color.a);

				Ref<Texture2D> texture = AssetManager::GetAsset<Texture2D>(quad.Texture);
				texture->Bind(0);
				quadTextureShader->SetInt1("u_Texture", 0);
				quadTextureShader->SetInt1("u_TilingFactor", quad.TilingFactor);

				RenderCommand::DrawIndexed(s_Data.QuadVAO, s_Data.QuadEBO->GetCount());
				s_Data.DrawCallsCount++;
			}
			quadTextureShader->UnBind();
		}

		s_CurrentState = RendererState::None;
	}

	void Renderer2D::BeginBatch()
	{
		s_CurrentState = RendererState::BeginBatch;
		s_RendererStateStack.emplace_back(RendererState::BeginBatch);

		StartBatch();
	}

	void Renderer2D::StartBatch() {
		s_Data.BatchQuadsToDraw.clear();

		s_Data.QuadIndexCount = 0;
		s_Data.QuadVertexBufferPtr = s_Data.QuadVertexBufferBase;
	}

	void Renderer2D::NextBatch() {
		Flush();
		StartBatch();
	}

	void Renderer2D::Flush() {
		if (s_Data.QuadIndexCount) {

			Ref<Shader> BatchColorShader = AssetManager::GetAsset<Shader>(s_Data.BatchColorShaderHandle);
			BatchColorShader->Bind();

			uint32_t dataSize = (uint32_t)((uint8_t*)s_Data.QuadVertexBufferPtr - (uint8_t*)s_Data.QuadVertexBufferBase);
			s_Data.BatchQuadVBO->SetSubData(s_Data.QuadVertexBufferBase, dataSize, 0);

			RenderCommand::DrawIndexed(s_Data.BatchQuadVAO, s_Data.QuadIndexCount);
			s_Data.DrawCallsCount++;

			BatchColorShader->UnBind();
		}
	}

	void Renderer2D::EndBatch()
	{
		KRX_CORE_ASSERT(s_CurrentState == RendererState::BeginBatch, "Forgot to call Renderer2D::BeginBatch()"); // Or you nested batches into each other that is also prohibited

		// Remove Shader and move into Shader Library
		if (s_Data.BatchQuadsToDraw.size() != 0) {
			std::sort(s_Data.BatchQuadsToDraw.begin(), s_Data.BatchQuadsToDraw.end(), [](const QuadData& q1, const QuadData& q2) {
				return q1.ZIndex < q2.ZIndex;
			});

			constexpr size_t quadVertexCount = 4;

			for (const auto& quad : s_Data.BatchQuadsToDraw) {

				if (s_Data.QuadIndexCount >= s_Data.MaxQuadIndices)
					NextBatch();

				glm::mat4 transform = glm::translate(glm::mat4(1.0f), quad.Position) *
					glm::rotate(glm::mat4(1.0f), glm::radians(quad.Rotation), glm::vec3(0.0f, 0.0f, 1.0f)) *
					glm::scale(glm::mat4(1.0f), glm::vec3(quad.Size, 1.0f));

				for (size_t i = 0; i < quadVertexCount; i++)
				{
					s_Data.QuadVertexBufferPtr->Position = transform * s_Data.QuadVertexPositions[i];
					s_Data.QuadVertexBufferPtr->Color = quad.Color;
					s_Data.QuadVertexBufferPtr++;
				}

				s_Data.QuadIndexCount += 6;
			}

			Flush();
		}
		
		s_CurrentState = RendererState::BeginFrame;
	}
	
	void Renderer2D::DrawQuad(glm::vec2 position, glm::vec2 size, glm::vec4 color) 
	{
		DrawQuad(glm::vec3(position, 0.0f), size, color);
	}

	void Renderer2D::DrawQuad(glm::vec3 position, glm::vec2 size, glm::vec4 color)
	{
		auto it = s_RendererStateStack.begin();
		if (it == s_RendererStateStack.end())
			KRX_CORE_ASSERT(false, "Forgot to call Renderer2D::BeginFrame()!");

		switch (s_CurrentState) 
		{
			case RendererState::BeginFrame: {
				s_Data.QuadsToDraw.emplace_back(position, size, 0.0f, s_Data.WhiteTextureHanle, 1, color, position.z);
				break;
			}
			case RendererState::BeginBatch: {
				s_Data.BatchQuadsToDraw.emplace_back(position, size, 0.0f, s_Data.WhiteTextureHanle,1, color, position.z);
				break;
			}
		}
	}

	void Renderer2D::DrawQuad(glm::vec2 position, glm::vec2 size, AssetHandle texture, uint16_t tilingFactor, glm::vec4 tintColor /*= glm::vec4(1.0f)*/) {
		DrawQuad(glm::vec3(position, 0.0f), size, texture, tilingFactor, tintColor);
	}

	void Renderer2D::DrawQuad(glm::vec3 position, glm::vec2 size, AssetHandle texture, uint16_t tilingFactor, glm::vec4 tintColor /*= glm::vec4(1.0f)*/) {
		auto it = s_RendererStateStack.begin();
		if (it == s_RendererStateStack.end())
			KRX_CORE_ASSERT(false, "Forgot to call Renderer2D::BeginFrame()!");

		switch (s_CurrentState)
		{
			case RendererState::BeginFrame: {
				s_Data.QuadsToDraw.emplace_back(position, size, 0.0f, texture, tilingFactor, tintColor, position.z);
				break;
			}
			case RendererState::BeginBatch: {
				s_Data.BatchQuadsToDraw.emplace_back(position, size, 0.0f, texture, tilingFactor, tintColor, position.z);
				break;
			}
		}
	}

	void Renderer2D::DrawRotatedQuad(glm::vec2 position, glm::vec2 size, float angle, glm::vec4 color)
	{
		DrawRotatedQuad(glm::vec3(position, 0.0f), size, angle, color);
	}

	void Renderer2D::DrawRotatedQuad(glm::vec3 position, glm::vec2 size, float angle, glm::vec4 color)
	{
		auto it = s_RendererStateStack.begin();
		if (it == s_RendererStateStack.end())
			KRX_CORE_ASSERT(false, "Forgot to call Renderer2D::BeginFrame()!");

		switch (s_CurrentState)
		{
			case RendererState::BeginFrame: {
				s_Data.QuadsToDraw.emplace_back(position, size, angle, s_Data.WhiteTextureHanle, 1, color, position.z);
				break;
			}
			case RendererState::BeginBatch: {
				s_Data.BatchQuadsToDraw.emplace_back(position, size, angle, s_Data.WhiteTextureHanle, 1, color, position.z);
				break;
			}
		}
	}

	void Renderer2D::DrawRotatedQuad(glm::vec2 position, glm::vec2 size, float angle, AssetHandle texture, uint16_t tilingFactor, glm::vec4 tintColor /*= glm::vec4(1.0f)*/) {
		DrawRotatedQuad(glm::vec3(position, 0.0f), size, angle, texture, tilingFactor, tintColor);
	}

	void Renderer2D::DrawRotatedQuad(glm::vec3 position, glm::vec2 size, float angle, AssetHandle texture, uint16_t tilingFactor, glm::vec4 tintColor /*= glm::vec4(1.0f)*/) {

		auto it = s_RendererStateStack.begin();
		if (it == s_RendererStateStack.end())
			KRX_CORE_ASSERT(false, "Forgot to call Renderer2D::BeginFrame()!");

		switch (s_CurrentState)
		{
			case RendererState::BeginFrame: {
				s_Data.QuadsToDraw.emplace_back(position, size, angle, texture, tilingFactor, tintColor, position.z);
				break;
			}
			case RendererState::BeginBatch: {
				s_Data.BatchQuadsToDraw.emplace_back(position, size, angle, texture, tilingFactor, tintColor, position.z);
				break;
			}
		}

	}

}