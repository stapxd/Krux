#include "SandboxWorldLayer.h"

// temp
#include <glad/glad.h>

void SandboxWorldLayer::OnAttach()
{
	// VAO
	VAO = Krux::VertexArray::Create();

	// VBO
	float vertices[3 * 3] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.0f,  0.5f, 0.0f
	};

	VBO = Krux::VertexBuffer::Create();
	VBO->SetData(vertices, sizeof(vertices), Krux::BufferUsage::StaticDraw);

	VAO->AttachVertexBuffer(VBO);

	// Layout
	glEnableVertexArrayAttrib(VAO->GetRendererID(), 0);
	glVertexArrayAttribFormat(VAO->GetRendererID(), 0, 3, GL_FLOAT, false, 0);
	glVertexArrayAttribBinding(VAO->GetRendererID(), 0, 0);

	// IBO
	unsigned int indices[3] = {
		0, 1, 2
	};

	EBO = Krux::IndexBuffer::Create();
	EBO->SetData(indices, sizeof(indices) / 4, Krux::BufferUsage::StaticDraw);

	VAO->AttachElementBuffer(EBO);
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
	// RenderCommand::DrawIndexed(VAO);
	VAO->Bind();
	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);
	VAO->UnBind();
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
