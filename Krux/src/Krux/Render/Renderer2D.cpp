#include "krxpch.h"
#include "Renderer2D.h"

#include "Krux/Core/Core.h"

#include "Assets/AssetManager.h"

#include "RenderCommand.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Krux {
	
	std::vector<RendererState> Renderer2D::s_RendererStateStack;
	RendererState Renderer2D::s_CurrentState = RendererState::None;

	RendererData Renderer2D::s_Data;

	void Renderer2D::Init()
	{
		s_Data.ColorShaderHandle = AssetManager::Load<Shader>("assets/builtin/shaders/color.glsl");

		s_Data.QuadVAO = VertexArray::Create();

		float vertices[4 * 3] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.5f,  0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f,
		};

		s_Data.QuadVBO = VertexBuffer::Create();
		s_Data.QuadVBO->SetData(vertices, sizeof(vertices), BufferUsage::StaticDraw);


		VertexLayout layout = {
			{ 3, VertexLayoutType::Float, false }
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

	void Renderer2D::BeginFrame()
	{
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
			Ref<Shader> colorShader = AssetManager::GetAsset<Shader>(s_Data.ColorShaderHandle);
			colorShader->Bind();
			for (const auto& quad : s_Data.QuadsToDraw) {
				
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), quad.Position) * glm::scale(glm::mat4(1.0f), glm::vec3(quad.Size, 1.0f));
				colorShader->SetMat4("u_Model", transform);

				colorShader->SetFloat4("u_Color", quad.Color.r, quad.Color.g, quad.Color.b, quad.Color.a);

				RenderCommand::DrawIndexed(s_Data.QuadVAO, s_Data.QuadEBO->GetCount());
			}
			colorShader->UnBind();

			s_Data.QuadsToDraw.clear();
		}

		s_RendererStateStack.clear();
		s_CurrentState = RendererState::None;
	}

	void Renderer2D::BeginBatch()
	{
		s_CurrentState = RendererState::BeginBatch;
		s_RendererStateStack.emplace_back(RendererState::BeginBatch);
	}

	void Renderer2D::EndBatch()
	{
		KRX_CORE_ASSERT(s_CurrentState == RendererState::BeginBatch, "Forgot to call Renderer2D::BeginBatch()"); // Or you nested batches into each other that is also prohibited



		s_CurrentState = RendererState::BeginFrame;
	}
	
	void Renderer2D::DrawQuad(glm::vec2 position, glm::vec2 size, glm::vec4 color) 
	{
		DrawQuad(glm::vec3(position, 0.0f), size, color);
	}

	void Renderer2D::DrawQuad(glm::vec3 position, glm::vec2 size, glm::vec4 color)
	{
		switch (s_CurrentState) 
		{
			case RendererState::BeginFrame: {
				auto it = s_RendererStateStack.begin();
				if (it == s_RendererStateStack.end())
					KRX_CORE_ASSERT(false, "Forgot to call Renderer2D::BeginFrame()!");

				s_Data.QuadsToDraw.emplace_back(position, size, 0.0f, color, position.z);
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


	}

}