#pragma once

#include "Assets/AssetManager.h"

#include "Camera.h"
#include "Structures/RenderData.h"

#include <glm/glm.hpp>

#include <vector>

#include "Krux/Scene/Components.h"

namespace Krux {

	enum class RendererState {
		None = 0,
		BeginFrame,
		BeginBatch
	};

	class Renderer2D {
	public:
		static void Init();
		static void Shutdown();
		
		static void BeginFrame(const Camera& camera);
		static void EndFrame();

		static void BeginBatch();
		static void EndBatch();
		
		static void DrawQuad(glm::vec2 position, glm::vec2 size, glm::vec4 color = glm::vec4(1.0f));
		static void DrawQuad(glm::vec3 position, glm::vec2 size, glm::vec4 color = glm::vec4(1.0f));
		static void DrawQuad(glm::vec2 position, glm::vec2 size, AssetHandle texture, float tilingFactor = 1.0f, glm::vec4 tintColor = glm::vec4(1.0f));
		static void DrawQuad(glm::vec3 position, glm::vec2 size, AssetHandle texture, float tilingFactor = 1.0f, glm::vec4 tintColor = glm::vec4(1.0f));

		static void DrawRotatedQuad(glm::vec2 position, glm::vec2 size, float angle, glm::vec4 color = glm::vec4(1.0f));
		static void DrawRotatedQuad(glm::vec3 position, glm::vec2 size, float angle, glm::vec4 color = glm::vec4(1.0f));
		static void DrawRotatedQuad(glm::vec2 position, glm::vec2 size, float angle, AssetHandle texture, float tilingFactor = 1.0f, glm::vec4 tintColor = glm::vec4(1.0f));
		static void DrawRotatedQuad(glm::vec3 position, glm::vec2 size, float angle, AssetHandle texture, float tilingFactor = 1.0f, glm::vec4 tintColor = glm::vec4(1.0f));

		static void DrawCircle(glm::vec2 position, float radius, glm::vec4 color, float thickness = 1.0f, float fade = 0.005f);
		static void DrawCircle(glm::vec3 position, float radius, glm::vec4 color, float thickness = 1.0f, float fade = 0.005f);

		static void DrawSprite(const Components::Transform& trm, const Components::SpriteRenderer sprR);

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