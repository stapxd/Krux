#include "SandboxWorldLayer.h"

// temp
#include "Krux/Render/VertexLayout.h"
#include "Krux/Render/RenderCommand.h"
#include "Krux/Render/Assets/AssetManager.h"

void SandboxWorldLayer::OnAttach()
{
	Krux::AssetHandle handle = Krux::AssetManager::Load<Krux::Shader>("assets/shaders/color.glsl");
	Shader = Krux::AssetManager::GetAsset<Krux::Shader>(handle);

	//Shader = Krux::Shader::Create("assets/shaders/color.glsl");

	// VAO
	{
		VAO = Krux::VertexArray::Create();
	}

	// VBO
	{
		float vertices[3 * 3] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.0f,  0.5f, 0.0f
		};

		VBO = Krux::VertexBuffer::Create();
		VBO->SetData(vertices, sizeof(vertices), Krux::BufferUsage::StaticDraw);
	}

	// Layout
	{
		Krux::VertexLayout layout = {
			{ 3, Krux::VertexLayoutType::Float, false }
		};

		VAO->AttachVertexBuffer(VBO, layout);
	}

	// IBO
	{
		unsigned int indices[3] = {
			0, 1, 2
		};

		EBO = Krux::IndexBuffer::Create();
		EBO->SetData(indices, sizeof(indices) / 4, Krux::BufferUsage::StaticDraw);

		VAO->AttachElementBuffer(EBO); 
	}
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
	Shader->Bind();
	Krux::RenderCommand::DrawIndexed(VAO, EBO->GetCount());
	Shader->UnBind();
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
