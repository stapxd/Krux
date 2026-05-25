#include "EditorLayer.h"

// Core
#include "Krux/Core/Application.h"
#include "Krux/Core/Input.h"

// Scene
#include "Krux/Scene/Entity.h"
#include "Krux/Scene/Components.h"

// temp
#include "Krux/Render/VertexLayout.h"
#include "Krux/Render/RenderCommand.h"
#include "Krux/Render/Assets/AssetManager.h"

#include "Krux/Render/Renderer2D.h"

namespace Krux {

	EditorLayer::EditorLayer()
		: Layer("Editor Layer"), m_Camera(Krux::Application::Instance()->GetWidth(), Application::Instance()->GetHeight()), m_CameraController(m_Camera),
		m_SceneHierarchyPanel(&m_Scene), m_InspectorPanel(&m_Scene)
	{
	}

	void EditorLayer::OnAttach()
	{
		TextureSpecification spec;
		spec.WrapR = TextureWrap::Repeat;
		spec.WrapS = TextureWrap::Repeat;
		spec.WrapT = TextureWrap::Repeat;

		m_Texture = AssetManager::Load<Texture2D>("assets/textures/CrackTexture.png", spec);
		//m_Texture = AssetManager::Load<Texture2D>("assets/shaders/color.glsl", spec);
		m_Texture2 = AssetManager::Load<Texture2D>("assets/textures/RedTexture.png", spec);

		FrameBufferSpecification fbSpec;
		fbSpec.Attachments = { FrameBufferAttachment::RGBA8, FrameBufferAttachment::Depth24_Stencil8 };
		fbSpec.Width = 1280;
		fbSpec.Height = 720;
		m_FrameBuffer = FrameBuffer::Create(fbSpec);

		// Temp
		Entity& e001 = m_Scene.CreateEntity();
		Entity& e002 = m_Scene.CreateEntity();
		Entity& e003 = m_Scene.CreateEntity();
		Entity& e004 = m_Scene.CreateEntity();

		e001.AddComponent<SpriteRendererComponent>(glm::vec4(1.0f), m_Texture);
		e002.AddComponent<SpriteRendererComponent>(glm::vec4(1.0f, 0.5f, 0.2f, 1.0f));

		TransformComponent* trm = e001.GetComponent<TransformComponent>();
		if (trm) {
			trm->LocalPosition.x -= 5.0f;
		}

		NameComponent* n1 = e001.GetComponent<NameComponent>();
		NameComponent* n2 = e002.GetComponent<NameComponent>();
		NameComponent* n3 = e003.GetComponent<NameComponent>();

		n1->Text = "E1";
		n2->Text = "E2";
		n3->Text = "E3";

		e001.AddChild(e002);
		e003.AddChild(e001);
		e004.AddChild(e001);

		e002.BecomeOrphan();

	}

	void EditorLayer::OnDetach()
	{
	}

	void EditorLayer::OnImGuiRender()
	{
		static bool show = true;
		ImGui::ShowDemoWindow(&show);

		ImGuiID dockspace_id = ImGui::GetID("MainDockspaceOverViewport");

		ImGui::DockSpaceOverViewport(dockspace_id, ImGui::GetMainViewport(), ImGuiDockNodeFlags_None);
        
		if (ImGui::BeginMainMenuBar())
		{
			if (ImGui::BeginMenu("Panels"))
			{
				ImGui::MenuItem("Viewport", "", m_ViewportPanel.Open());
				ImGui::MenuItem("Scene Hierarchy", "", m_SceneHierarchyPanel.Open());
				ImGui::MenuItem("Inspector", "", m_InspectorPanel.Open());
				ImGui::EndMenu();
			}
			ImGui::EndMainMenuBar();
		}

		// TODO: future look
		// m_SceneHirarchypPanel.Render();
		// m_InspectorPanel.Render();
		// m_ViewportPanel.Render();
		// m_FileSystemPanel.Render();
		// m_StatsPanel.Render();

		// Modal window if deleting entity has children
		if (m_EntityToDelete != UUID64::INVALID) {
			Entity* entityToDelete = m_Scene.FindByUUID(m_EntityToDelete);

			if (entityToDelete && !entityToDelete->GetChildEntities().empty()) {
				ImVec2 center = ImGui::GetMainViewport()->GetCenter();
				ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));

				ImGui::OpenPopup("Delete?");
				if (ImGui::BeginPopupModal("Delete?", NULL, ImGuiWindowFlags_AlwaysAutoResize))
				{
					ImGui::Text("Entity has child entities in it.\nThis operation cannot be undone!");
					ImGui::Separator();

					if (ImGui::Button("OK", ImVec2(120, 0))) { 
						m_EntityToDelete = UUID64::INVALID;
						m_Scene.DeleteEntity(*entityToDelete);
						ImGui::CloseCurrentPopup();
					}
					ImGui::SameLine();
					if (ImGui::Button("Cancel", ImVec2(120, 0))) { 
						m_EntityToDelete = UUID64::INVALID;
						ImGui::CloseCurrentPopup(); 
					}
					ImGui::EndPopup();
				}
			}
			else if (entityToDelete) {
				m_Scene.DeleteEntity(*entityToDelete);
			}
			else {
				m_EntityToDelete = UUID64::INVALID;
			}
		}

		ImGui::Begin("Stats");
			ImGui::Text("Draw Calls: %d", Renderer2D::GetDrawCallsCount());
		ImGui::End();

		ImGuiLayer* imguiLayer = Application::Instance()->GetImGuiLayer();

		imguiLayer->BeginWindowCollection();

		m_ViewportPanel.OnRender(m_FrameBuffer->GetAttachmentID(0), ImGuiWindowFlags_NoScrollbar);
		imguiLayer->RegisterWindowState(m_ViewportPanel.IsFocused(), m_ViewportPanel.IsHovered());

		m_InspectorPanel.OnRender(m_SceneHierarchyPanel.SelectedEntityID());
		imguiLayer->RegisterWindowState(m_InspectorPanel.IsFocused(), m_InspectorPanel.IsHovered());

		m_SceneHierarchyPanel.OnRender();
		imguiLayer->RegisterWindowState(m_SceneHierarchyPanel.IsFocused(), m_SceneHierarchyPanel.IsHovered());

		imguiLayer->EndWindowCollection();
	}

	void EditorLayer::OnUpdate(Time time)
	{
		glm::vec2 viewportSize = m_ViewportPanel.GetSize();
		if (m_ViewportPanel.ShouldUpdateExternalViewport())
		{
			viewportSize = m_ViewportPanel.GetSize();
			m_FrameBuffer->Resize((uint32_t)viewportSize.x, (uint32_t)viewportSize.y);
			m_Camera.SetViewport((uint32_t)viewportSize.x, (uint32_t)viewportSize.y);
		}

		// Render

		m_FrameBuffer->Bind();
		Renderer::Clear();
		Renderer::SetViewport(0, 0, (uint32_t)viewportSize.x, (uint32_t)viewportSize.y);

		switch (m_Scene.GetState())
		{
			case SceneState::Edit:
			{
				if (m_ViewportPanel.IsFocused())
					m_CameraController.OnUpdate(time);

				m_Scene.OnUpdateEdit(time, m_Camera);
				break;
			}
			case SceneState::Play: 
			{
				break;
			}
		}

		m_FrameBuffer->UnBind();

		/*m_FrameBuffer->Bind();
		Renderer::Clear();

		Renderer::SetViewport(0, 0, (uint32_t)viewportSize.x, (uint32_t)viewportSize.y);

		Renderer2D::BeginFrame(m_Camera);

			Renderer2D::BeginBatch();
				Renderer2D::DrawCircle({ -0.5, -0.5 }, 1.0f, { 0.0f, 1.0f, 1.0f, 1.0f });
				Renderer2D::DrawCircle({ 0.5, -0.5 }, 0.5f, { 1.0f, 0.0f, 0.0f, 1.0f });
				Renderer2D::DrawQuad({ 0.5,  0.5 }, glm::vec2(1.0f), { 0.0f, 0.0f, 1.0f, 1.0f });
				Renderer2D::DrawQuad({ -0.5, 0.5 }, glm::vec2(1.0f), m_Texture, 5, { 1.0f, 1.0f, 1.0f, 1.0f });
				Renderer2D::DrawQuad({ -1.5, 0.5 }, glm::vec2(1.0f), m_Texture2, 5, { 1.0f, 1.0f, 1.0f, 1.0f });
			Renderer2D::EndBatch();

		Renderer2D::EndFrame();

		m_FrameBuffer->UnBind();*/
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
		if (m_SceneHierarchyPanel.IsFocused() && e.GetKey() == (int)Key::DEL) {
			
			m_EntityToDelete = m_SceneHierarchyPanel.SelectedEntityID();
		}

		return true;
	}

	bool EditorLayer::OnMouseScroll(MouseScrollEvent& e)
	{
		if(m_ViewportPanel.IsHovered())
			m_CameraController.AddZoom(-(float)e.GetYOffset());

		return true;
	}


	bool EditorLayer::OnWindowResize(WindowResizeEvent& e)
	{
		//m_Camera.SetViewport(e.GetWidth(), e.GetHeight());
		return true;
	}

}