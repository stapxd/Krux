#include "SandboxWorldLayer.h"

// temp
#include <glad/glad.h>

void SandboxWorldLayer::OnAttach()
{
	// VAO
	glCreateVertexArrays(1, &VAO);

	// VBO
	float vertices[3 * 3] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.0f,  0.5f, 0.0f
	};

	glCreateBuffers(1, &VBO);
	glNamedBufferData(VBO, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexArrayVertexBuffer(VAO, 0, VBO, 0, 3 * sizeof(float));

	// Layout
	glEnableVertexArrayAttrib(VAO, 0);
	glVertexArrayAttribFormat(VAO, 0, 3, GL_FLOAT, false, 0);
	glVertexArrayAttribBinding(VAO, 0, 0);

	// IBO
	unsigned int indices[3] = {
		0, 1, 2
	};
	glCreateBuffers(1, &IBO);
	glNamedBufferData(IBO, sizeof(indices), indices, GL_STATIC_DRAW);
	glVertexArrayElementBuffer(VAO, IBO);
}

void SandboxWorldLayer::OnDetach()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &IBO);
}

void SandboxWorldLayer::OnImGuiRender()
{
	static bool show = true;
	ImGui::ShowDemoWindow(&show);
}

void SandboxWorldLayer::OnUpdate()
{
	glBindVertexArray(VAO);
	// Render
	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);
	//glDrawArrays(GL_TRIANGLES, 1, 3);
	glBindVertexArray(0);
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
