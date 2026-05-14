#include "EditorLayer.h"

// temp
#include "Krux/Render/VertexLayout.h"
#include "Krux/Render/RenderCommand.h"
#include "Krux/Render/Assets/AssetManager.h"

#include "Krux/Render/Renderer2D.h"
#include "Krux/Core/Input.h"

namespace Krux {

	void EditorLayer::OnAttach()
	{
		TextureSpecification spec;
		spec.WrapR = TextureWrap::Repeat;
		spec.WrapS = TextureWrap::Repeat;
		spec.WrapT = TextureWrap::Repeat;

		m_Texture = AssetManager::Load<Texture2D>("assets/textures/CrackTexture.png", spec);
		m_Texture2 = AssetManager::Load<Texture2D>("assets/textures/RedTexture.png", spec);
	}

	void EditorLayer::OnDetach()
	{
	}

	void EditorLayer::OnImGuiRender()
	{
		/*static bool show = true;
		ImGui::ShowDemoWindow(&show);*/

		ImGui::Begin("Stats");

		ImGui::Text("Draw Calls: %d", Renderer2D::GetDrawCallsCount());

		ImGui::End();
	}

	void EditorLayer::OnUpdate(Time time)
	{
		m_CameraController.OnUpdate(time);

		// Render
		Renderer2D::BeginFrame(m_Camera);

			Renderer2D::BeginBatch();
				Renderer2D::DrawCircle({ -0.5, -0.5 }, 1.0f, { 0.0f, 1.0f, 1.0f, 1.0f });
				Renderer2D::DrawCircle({ 0.5, -0.5 }, 0.5f, { 1.0f, 0.0f, 0.0f, 1.0f });
				Renderer2D::DrawQuad({ 0.5,  0.5 }, glm::vec2(1.0f), { 0.0f, 0.0f, 1.0f, 1.0f });
				Renderer2D::DrawQuad({ -0.5, 0.5 }, glm::vec2(1.0f), m_Texture, 5, { 1.0f, 1.0f, 1.0f, 1.0f });
				Renderer2D::DrawQuad({ -1.5, 0.5 }, glm::vec2(1.0f), m_Texture2, 5, { 1.0f, 1.0f, 1.0f, 1.0f });
			Renderer2D::EndBatch();

		Renderer2D::EndFrame();
	}

	void EditorLayer::OnEvent(Event& e)
	{
		EventDispatcher d(e);

		d.Dispatch<KeyPressedEvent>(BIND_EVENT_FUNC(OnKeyPressed));
		d.Dispatch<WindowResizeEvent>(BIND_EVENT_FUNC(OnWindowResize));
		d.Dispatch<MouseScrollEvent>(BIND_EVENT_FUNC(OnMouseScroll));
	}

	bool EditorLayer::OnKeyPressed(KeyPressedEvent& e)
	{
		return true;
	}

	bool EditorLayer::OnMouseScroll(MouseScrollEvent& e)
	{
		m_CameraController.AddZoom(-(float)e.GetYOffset());
		return true;
	}


	bool EditorLayer::OnWindowResize(WindowResizeEvent& e)
	{
		m_Camera.SetViewport(e.GetWidth(), e.GetHeight());
		return true;
	}

}