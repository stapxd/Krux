#include "SandboxWorldLayer.h"

// temp
#include "Krux/Render/VertexLayout.h"
#include "Krux/Render/RenderCommand.h"
#include "Krux/Render/Assets/AssetManager.h"

#include "Krux/Render/Renderer2D.h"

void SandboxWorldLayer::OnAttach()
{
}

void SandboxWorldLayer::OnDetach()
{
}

void SandboxWorldLayer::OnImGuiRender()
{
	static bool show = true;
	ImGui::ShowDemoWindow(&show);
}

void SandboxWorldLayer::OnUpdate()
{
	// Render

	Krux::Renderer2D::BeginFrame();

	Krux::Renderer2D::DrawQuad({ -0.5, -0.5 }, glm::vec2(1.0f), { 1.0f, 0.0f, 0.0f, 1.0f });
	Krux::Renderer2D::DrawQuad({  0.5, -0.5 }, glm::vec2(1.0f), { 0.0f, 1.0f, 0.0f, 1.0f });
	Krux::Renderer2D::DrawQuad({  0.5,  0.5 }, glm::vec2(1.0f), { 0.0f, 0.0f, 1.0f, 1.0f });
	Krux::Renderer2D::DrawRotatedQuad({ -0.5,  0.5, -1.0f }, glm::vec2(1.0f), 45.0f, { 0.0f, 1.0f, 1.0f, 1.0f });

	Krux::Renderer2D::EndFrame();

	/*Shader->Bind();
	Krux::RenderCommand::DrawIndexed(VAO, EBO->GetCount());
	Shader->UnBind();*/
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
