#include "SandboxWorldLayer.h"

// temp
#include "Krux/Render/VertexLayout.h"
#include "Krux/Render/RenderCommand.h"
#include "Krux/Render/Assets/AssetManager.h"

#include "Krux/Render/Renderer2D.h"
#include "Krux/Core/Input.h"

void SandboxWorldLayer::OnAttach()
{
	Krux::TextureSpecification spec;
	spec.WrapR = Krux::TextureWrap::Repeat;
	spec.WrapS = Krux::TextureWrap::Repeat;
	spec.WrapT = Krux::TextureWrap::Repeat;

	m_Texture = Krux::AssetManager::Load<Krux::Texture2D>("assets/textures/CrackTexture.png", spec);
	m_Texture2 = Krux::AssetManager::Load<Krux::Texture2D>("assets/textures/RedTexture.png",  spec);
}

void SandboxWorldLayer::OnDetach()
{
}

void SandboxWorldLayer::OnImGuiRender()
{
	/*static bool show = true;
	ImGui::ShowDemoWindow(&show);*/

	ImGui::Begin("Stats");

	ImGui::Text("Draw Calls: %d", Krux::Renderer2D::GetDrawCallsCount());

	ImGui::End();
}

void SandboxWorldLayer::OnUpdate(Krux::Time time)
{
	static float rotation = 0.0f;
	rotation += 45.0f * time.DeltaTime();
	// Render
	Krux::Renderer2D::BeginFrame(m_Camera);

		Krux::Renderer2D::BeginBatch();
			Krux::Renderer2D::DrawQuad({  0.5,  0.5 }, glm::vec2(1.0f), { 0.0f, 0.0f, 1.0f, 1.0f });
			Krux::Renderer2D::DrawRotatedQuad({ -0.5,  0.5, -1.0f }, glm::vec2(1.0f), 45.0f, { 0.0f, 1.0f, 1.0f, 1.0f });

			Krux::Renderer2D::DrawRotatedQuad({ 0.5, -0.5 }, glm::vec2(1.0f), rotation, m_Texture2, 1, { 1.0f, 1.0f, 1.0f, 1.0f });
			Krux::Renderer2D::DrawQuad({ -0.5, -0.5 }, glm::vec2(1.0f), m_Texture, 5, { 1.0f, 1.0f, 1.0f, 1.0f });
		Krux::Renderer2D::EndBatch();

		/*Krux::Renderer2D::BeginBatch();
			Krux::Renderer2D::DrawRotatedQuad({ 0.5, -0.5 }, glm::vec2(1.0f), 45.0f, m_Texture2, 1, { 1.0f, 1.0f, 1.0f, 1.0f });
			Krux::Renderer2D::DrawQuad({ -0.5, -0.5 }, glm::vec2(1.0f), m_Texture, 5, { 0.0f, 1.0f, 1.0f, 1.0f });
		Krux::Renderer2D::EndBatch();*/

	Krux::Renderer2D::EndFrame();
}

void SandboxWorldLayer::OnEvent(Krux::Event& e)
{
	Krux::EventDispatcher d(e);

	d.Dispatch<Krux::KeyPressedEvent>(BIND_EVENT_FUNC(OnKeyPressed));
}

bool SandboxWorldLayer::OnKeyPressed(Krux::KeyPressedEvent& e)
{
	KRX_TRACE("{}", (char)e.GetKey());
	return true;
}
