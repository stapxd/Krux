#include "krxpch.h"
#include "Renderer2D.h"

#include "Krux/Core/Core.h"

#include "Assets/AssetManager.h"
#include "Krux/Render/Assets/Shader.h"
#include "Krux/Render/Assets/Texture2D.h"
#include "ShaderLibrary.h"

#include "RenderCommand.h"

#include <glm/gtc/matrix_transform.hpp>

#include <cassert>

namespace Krux {
	
	std::vector<RendererState> Renderer2D::s_RendererStateStack;
	RendererState Renderer2D::s_CurrentState = RendererState::None;

	RendererData Renderer2D::s_Data;

	void Renderer2D::Init()
	{

		s_Data.WhiteTextureHanle = AssetManager::CreateMemoryOnlyAsset<Texture2D>();
		uint32_t white = 0xffffffff;
		AssetManager::GetAsset<Texture2D>(s_Data.WhiteTextureHanle)->SetData(&white, sizeof(uint32_t));

		s_Data.CameraUniform = UniformBuffer::Create(sizeof(RendererData::CameraData), 0, BufferUsage::DynamicDraw);

		// Batch draw
		{
			KRX_CORE_ASSERT(s_Data.MaxQuads != 0, "Batch Max Quads should not be 0!");

			// Quads
			{
				s_Data.QuadVertexPositions[0] = { -0.5f, -0.5f, 0.0f, 1.0f };
				s_Data.QuadVertexPositions[1] = { 0.5f, -0.5f, 0.0f, 1.0f };
				s_Data.QuadVertexPositions[2] = { 0.5f,  0.5f, 0.0f, 1.0f };
				s_Data.QuadVertexPositions[3] = { -0.5f,  0.5f, 0.0f, 1.0f };

				s_Data.QuadTexCoords[0] = { 0.0f, 0.0f };
				s_Data.QuadTexCoords[1] = { 1.0f, 0.0f };
				s_Data.QuadTexCoords[2] = { 1.0f, 1.0f };
				s_Data.QuadTexCoords[3] = { 0.0f, 1.0f };

				s_Data.BatchQuadShaderHandle = ShaderLibrary::Load("assets/builtin/shaders/QuadTextureBatch.glsl");

				s_Data.BatchQuadVAO = VertexArray::Create();

				s_Data.BatchQuadVBO = VertexBuffer::Create();
				s_Data.BatchQuadVBO->SetData(nullptr, s_Data.MaxQuadVertices * sizeof(QuadVertex), BufferUsage::DynamicDraw);

				VertexLayout quadBatchLayout = {
					{ 3, VertexLayoutType::Float, false }, // Position
					{ 4, VertexLayoutType::Float, false }, // Color
					{ 2, VertexLayoutType::Float, false }, // TexCoords
					{ 1, VertexLayoutType::Float, false }, // TexIndex
					{ 1, VertexLayoutType::Float, false }, // TilingFactor
				};

				s_Data.BatchQuadVAO->AttachVertexBuffer(s_Data.BatchQuadVBO, quadBatchLayout);

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

				s_Data.TextureSlots[0] = s_Data.WhiteTextureHanle;
				s_Data.TextureIndex = 1;
			}

			// Circles
			{
				s_Data.BatchCircleShaderHandle = ShaderLibrary::Load("assets/builtin/shaders/CircleBatch.glsl");

				s_Data.BatchCircleVAO = VertexArray::Create();

				s_Data.BatchCircleVBO = VertexBuffer::Create();
				s_Data.BatchCircleVBO->SetData(nullptr, s_Data.MaxQuadVertices * sizeof(CircleVertex), BufferUsage::DynamicDraw);

				VertexLayout circleBatchLayout = {
					{ 3, VertexLayoutType::Float, false }, // Position
					{ 4, VertexLayoutType::Float, false }, // Color
					{ 2, VertexLayoutType::Float, false }, // Local Space Coords
					{ 1, VertexLayoutType::Float, false }, // Thickness
					{ 1, VertexLayoutType::Float, false }, // Fade
				};

				s_Data.BatchCircleVAO->AttachVertexBuffer(s_Data.BatchCircleVBO, circleBatchLayout);

				s_Data.CircleVertexBufferBase = new CircleVertex[s_Data.MaxQuadVertices];

				s_Data.BatchCircleVAO->AttachElementBuffer(s_Data.BatchQuadEBO);
			}

			// Textures
			for (int32_t i = 0; i < 32; i++)
				s_Data.Samplers[i] = i;
		}

		// Regular draw
		{
			s_Data.QuadTextureShaderHandle = ShaderLibrary::Load("assets/builtin/shaders/QuadTexture.glsl");
			s_Data.CircleShaderHandle = ShaderLibrary::Load("assets/builtin/shaders/Circle.glsl");

			// Quad
			{
				s_Data.QuadVAO = VertexArray::Create();

				float quadVertices[4 * 5] = {
					-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
					 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
					 0.5f,  0.5f, 0.0f,	1.0f, 1.0f,
					-0.5f,  0.5f, 0.0f,	0.0f, 1.0f
				};

				s_Data.QuadVBO = VertexBuffer::Create();
				s_Data.QuadVBO->SetData(quadVertices, sizeof(quadVertices), BufferUsage::StaticDraw);


				VertexLayout quadLayout = {
					{ 3, VertexLayoutType::Float, false }, // Position
					{ 2, VertexLayoutType::Float, false }  // Texture Coords
				};

				s_Data.QuadVAO->AttachVertexBuffer(s_Data.QuadVBO, quadLayout);

				unsigned int indices[6] = {
					0, 1, 2,
					2, 3, 0
				};

				s_Data.QuadEBO = IndexBuffer::Create();
				s_Data.QuadEBO->SetData(indices, sizeof(indices) / 4, BufferUsage::StaticDraw);

				s_Data.QuadVAO->AttachElementBuffer(s_Data.QuadEBO);
			}

			// Circle
			{
				s_Data.CircleVAO = VertexArray::Create();

				float circleVertices[4 * 5] = {
					-0.5f, -0.5f, 0.0f, -1.0f, -1.0f,
					 0.5f, -0.5f, 0.0f,  1.0f, -1.0f,
					 0.5f,  0.5f, 0.0f,	 1.0f,  1.0f,
					-0.5f,  0.5f, 0.0f,	-1.0f,  1.0f
				};

				s_Data.CircleVBO = VertexBuffer::Create();
				s_Data.CircleVBO->SetData(circleVertices, sizeof(circleVertices), BufferUsage::StaticDraw);

				VertexLayout circleLayout = {
					{ 3, VertexLayoutType::Float, false }, // Position
					{ 2, VertexLayoutType::Float, false }  // LocalSpaceCoords
				};

				s_Data.CircleVAO->AttachVertexBuffer(s_Data.CircleVBO, circleLayout);
				s_Data.CircleVAO->AttachElementBuffer(s_Data.QuadEBO);
			}
		}

	}

	void Renderer2D::Shutdown() 
	{
		delete[] s_Data.QuadVertexBufferBase;
	}

	void Renderer2D::BeginFrame(const Camera& camera)
	{
		// Camera
		s_Data.CameraSettings.ProjectionView = camera.GetProjectionView();
		s_Data.CameraUniform->SetData(&s_Data.CameraSettings, sizeof(RendererData::CameraData));

		s_RendererStateStack.clear();
		s_Data.QuadsToDraw.clear();
		s_Data.CirclesToDraw.clear();

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

		// Quad Draw
		if (s_Data.QuadsToDraw.size() != 0) {
			std::sort(s_Data.QuadsToDraw.begin(), s_Data.QuadsToDraw.end(), [](const QuadData& q1, const QuadData& q2) {
				return q1.ZIndex < q2.ZIndex;
			});

			Ref<Shader> quadTextureShader = ShaderLibrary::Get(s_Data.QuadTextureShaderHandle);
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
				quadTextureShader->SetFloat("u_TilingFactor", quad.TilingFactor);

				RenderCommand::DrawIndexed(s_Data.QuadVAO, s_Data.QuadEBO->GetCount());
				s_Data.DrawCallsCount++;
			}
			quadTextureShader->UnBind();
		}

		// Circle Draw
		if (s_Data.CirclesToDraw.size() != 0) {
			std::sort(s_Data.CirclesToDraw.begin(), s_Data.CirclesToDraw.end(), [](const CircleData& q1, const CircleData& q2) {
				return q1.ZIndex < q2.ZIndex;
			});

			Ref<Shader> circleShader = ShaderLibrary::Get(s_Data.CircleShaderHandle);
			circleShader->Bind();

			for (auto& circle : s_Data.CirclesToDraw) {

				glm::mat4 transform = glm::translate(glm::mat4(1.0f), circle.Position) *
					glm::scale(glm::mat4(1.0f), glm::vec3(circle.Radius * 2, circle.Radius * 2, 1.0f));
				circleShader->SetMat4("u_Model", transform);

				circleShader->SetFloat4("u_Color", circle.Color.r, circle.Color.g, circle.Color.b, circle.Color.a);
				circleShader->SetFloat("u_Thickness", circle.Thickness);
				circleShader->SetFloat("u_Fade", circle.Fade);

				RenderCommand::DrawIndexed(s_Data.CircleVAO, s_Data.QuadEBO->GetCount());
				s_Data.DrawCallsCount++;
			}
			circleShader->UnBind();
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

		// Quads
		{
			s_Data.BatchQuadsToDraw.clear();
			s_Data.QuadIndexCount = 0;
			s_Data.QuadVertexBufferPtr = s_Data.QuadVertexBufferBase;
		}

		// Circles
		{
			s_Data.BatchCirclesToDraw.clear();
			s_Data.CircleIndexCount = 0;
			s_Data.CircleVertexBufferPtr = s_Data.CircleVertexBufferBase;
		}

		s_Data.TextureIndex = 1;
	}

	void Renderer2D::NextBatch() {
		Flush();
		StartBatch();
	}

	void Renderer2D::Flush() {
		// Quads
		if (s_Data.QuadIndexCount) {
			Ref<Shader> BatchQuadShader = ShaderLibrary::Get(s_Data.BatchQuadShaderHandle);
			BatchQuadShader->Bind();

			uint32_t dataSize = (uint32_t)((uint8_t*)s_Data.QuadVertexBufferPtr - (uint8_t*)s_Data.QuadVertexBufferBase);
			s_Data.BatchQuadVBO->SetSubData(s_Data.QuadVertexBufferBase, dataSize, 0);

			for (uint32_t i = 0; i < s_Data.TextureIndex; i++) {
				//KRX_CORE_INFO("Texture id: {}",AssetManager::GetAsset<Texture2D>(s_Data.TextureSlots[i])->GetRendererID());
				AssetManager::GetAsset<Texture2D>(s_Data.TextureSlots[i])->Bind(i);
			}

			BatchQuadShader->SetIntV("u_Textures", 32, s_Data.Samplers);
			
			RenderCommand::DrawIndexed(s_Data.BatchQuadVAO, s_Data.QuadIndexCount);
			s_Data.DrawCallsCount++;

			BatchQuadShader->UnBind();
		}

		// Circles
		if (s_Data.CircleIndexCount) {
			Ref<Shader> BatchCircleShader = ShaderLibrary::Get(s_Data.BatchCircleShaderHandle);
			BatchCircleShader->Bind();

			uint32_t dataSize = (uint32_t)((uint8_t*)s_Data.CircleVertexBufferPtr - (uint8_t*)s_Data.CircleVertexBufferBase);
			s_Data.BatchCircleVBO->SetSubData(s_Data.CircleVertexBufferBase, dataSize, 0);

			RenderCommand::DrawIndexed(s_Data.BatchCircleVAO, s_Data.CircleIndexCount);
			s_Data.DrawCallsCount++;

			BatchCircleShader->UnBind();
		}
	}

	void Renderer2D::EndBatch()
	{
		KRX_CORE_ASSERT(s_CurrentState == RendererState::BeginBatch, "Forgot to call Renderer2D::BeginBatch()"); // Or you nested batches into each other that is also prohibited

		// Quads
		if (s_Data.BatchQuadsToDraw.size() != 0) {
			std::sort(s_Data.BatchQuadsToDraw.begin(), s_Data.BatchQuadsToDraw.end(), [](const QuadData& q1, const QuadData& q2) {
				return q1.ZIndex < q2.ZIndex;
			});

			constexpr size_t quadVertexCount = 4;

			for (const auto& quad : s_Data.BatchQuadsToDraw) {

				if (s_Data.QuadIndexCount >= s_Data.MaxQuadIndices)
					NextBatch();

				float texIndex = -1.0f;
				for (uint32_t i = 0; i < s_Data.TextureIndex; i++) {
					if (s_Data.TextureSlots[i] == quad.Texture) {
						texIndex = (float)i;
						break;
					}
				}

				if (texIndex == -1.0f) {
					if (s_Data.TextureIndex >= s_Data.MaxTextureSlots)
						NextBatch();

					s_Data.TextureSlots[s_Data.TextureIndex] = quad.Texture;
					texIndex = (float)s_Data.TextureIndex;
					s_Data.TextureIndex++;

					//KRX_CORE_INFO("texIndex assigned: {}, TextureIndex now: {}", texIndex, s_Data.TextureIndex);
				}

				glm::mat4 transform = glm::translate(glm::mat4(1.0f), quad.Position) *
					glm::rotate(glm::mat4(1.0f), glm::radians(quad.Rotation), glm::vec3(0.0f, 0.0f, 1.0f)) *
					glm::scale(glm::mat4(1.0f), glm::vec3(quad.Size, 1.0f));

				for (size_t i = 0; i < quadVertexCount; i++)
				{
					s_Data.QuadVertexBufferPtr->Position = transform * s_Data.QuadVertexPositions[i];
					s_Data.QuadVertexBufferPtr->Color = quad.Color;
					s_Data.QuadVertexBufferPtr->TextureCoords = s_Data.QuadTexCoords[i];
					s_Data.QuadVertexBufferPtr->TextureIndex = texIndex;
					s_Data.QuadVertexBufferPtr->TilingFactor = quad.TilingFactor;
					s_Data.QuadVertexBufferPtr++;
				}

				s_Data.QuadIndexCount += 6;
			}

		}
		
		// Circles
		if (s_Data.BatchCirclesToDraw.size() != 0) {
			std::sort(s_Data.BatchCirclesToDraw.begin(), s_Data.BatchCirclesToDraw.end(), [](const CircleData& q1, const CircleData& q2) {
				return q1.ZIndex < q2.ZIndex;
				});

			constexpr size_t CircleVertexCount = 4;

			for (const auto& circle : s_Data.BatchCirclesToDraw) {

				if (s_Data.CircleIndexCount >= s_Data.MaxQuadIndices)
					NextBatch();

				glm::mat4 transform = glm::translate(glm::mat4(1.0f), circle.Position) *
					glm::scale(glm::mat4(1.0f), glm::vec3(circle.Radius * 2, circle.Radius * 2, 1.0f));

				for (size_t i = 0; i < CircleVertexCount; i++)
				{
					s_Data.CircleVertexBufferPtr->Position = transform * s_Data.QuadVertexPositions[i];
					s_Data.CircleVertexBufferPtr->Color = circle.Color;
					s_Data.CircleVertexBufferPtr->LocalSpaceCoord = s_Data.QuadVertexPositions[i] * 2.0f;
					s_Data.CircleVertexBufferPtr->Thickness = circle.Thickness;
					s_Data.CircleVertexBufferPtr->Fade = circle.Fade;
					s_Data.CircleVertexBufferPtr++;
				}

				s_Data.CircleIndexCount += 6;
			}

		}

		Flush();

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
				s_Data.QuadsToDraw.emplace_back(position, size, 0.0f, s_Data.WhiteTextureHanle, 1.0f, color, position.z);
				break;
			}
			case RendererState::BeginBatch: {
				s_Data.BatchQuadsToDraw.emplace_back(position, size, 0.0f, s_Data.WhiteTextureHanle, 1.0f, color, position.z);
				break;
			}
		}
	}

	void Renderer2D::DrawQuad(glm::vec2 position, glm::vec2 size, AssetHandle texture, float tilingFactor, glm::vec4 tintColor /*= glm::vec4(1.0f)*/) {
		DrawQuad(glm::vec3(position, 0.0f), size, texture, tilingFactor, tintColor);
	}
	
	void Renderer2D::DrawQuad(glm::vec3 position, glm::vec2 size, AssetHandle texture, float tilingFactor, glm::vec4 tintColor /*= glm::vec4(1.0f)*/) {
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
				s_Data.QuadsToDraw.emplace_back(position, size, angle, s_Data.WhiteTextureHanle, 1.0f, color, position.z);
				break;
			}
			case RendererState::BeginBatch: {
				s_Data.BatchQuadsToDraw.emplace_back(position, size, angle, s_Data.WhiteTextureHanle, 1.0f, color, position.z);
				break;
			}
		}
	}

	void Renderer2D::DrawRotatedQuad(glm::vec2 position, glm::vec2 size, float angle, AssetHandle texture, float tilingFactor, glm::vec4 tintColor /*= glm::vec4(1.0f)*/) {
		DrawRotatedQuad(glm::vec3(position, 0.0f), size, angle, texture, tilingFactor, tintColor);
	}

	void Renderer2D::DrawRotatedQuad(glm::vec3 position, glm::vec2 size, float angle, AssetHandle texture, float tilingFactor, glm::vec4 tintColor /*= glm::vec4(1.0f)*/) {

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

	void Renderer2D::DrawCircle(glm::vec2 position, float radius, glm::vec4 color, float thickness /* = 1.0f*/, float fade /*= 0.005f*/) {
		DrawCircle(glm::vec3(position, 0.0f), radius, color, thickness, fade);
	}

	void Renderer2D::DrawCircle(glm::vec3 position, float radius, glm::vec4 color, float thickness /*= 1.0f*/, float fade /*= 0.005f*/) {
		auto it = s_RendererStateStack.begin();
		if (it == s_RendererStateStack.end())
			KRX_CORE_ASSERT(false, "Forgot to call Renderer2D::BeginFrame()!");

		switch (s_CurrentState)
		{
			case RendererState::BeginFrame: {
				s_Data.CirclesToDraw.emplace_back(position, radius, color, thickness, fade, position.z);
				break;
			}
			case RendererState::BeginBatch: {
				s_Data.BatchCirclesToDraw.emplace_back(position, radius, color, thickness, fade, position.z);
				break;
			}
		}
	}
}