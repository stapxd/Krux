#include "krxpch.h"
#include "ImGuiLayer.h"

#include "Krux/Core/Application.h"

#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

#include <GLFW/glfw3.h>

namespace Krux {
	ImGuiLayer::ImGuiLayer()
		: Layer("Imgui Layer")
	{

	}

	void ImGuiLayer::OnAttach()
	{
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;       // Enable Multi-Viewport / Platform Windows
		//io.ConfigViewportsNoAutoMerge = true;
		//io.ConfigViewportsNoTaskBarIcon = true;

		ImFont* openSansRegular = io.Fonts->AddFontFromFileTTF("assets/builtin/fonts/OpenSans/static/OpenSans-Regular.ttf", 18.0f);
		io.FontDefault = openSansRegular;

		// Setup Dear ImGui style
		ImGui::StyleColorsDark();

		ImGui_ImplGlfw_InitForOpenGL((GLFWwindow*)Application::Instance()->GetWindow()->GetNativeWindow(), true);
		ImGui_ImplOpenGL3_Init("#version 450");
	}

	void ImGuiLayer::OnDetach()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

	void ImGuiLayer::OnEvent(Event& e)
	{
		if (m_BlockEvents) {
			ImGuiIO& io = ImGui::GetIO();
			e.IsHandled |= e.IsInCategory(KeyEvent) && io.WantCaptureKeyboard;
			e.IsHandled |= e.IsInCategory(MouseButtonEvent) && io.WantCaptureMouse;
		}
	}

	void ImGuiLayer::Begin()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	}

	void ImGuiLayer::End()
	{
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		ImGuiIO& io = ImGui::GetIO(); (void)io;
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			GLFWwindow* backup_current_context = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(backup_current_context);
		}
	}

	void ImGuiLayer::SetBlockEvents(bool value) {
		if (m_BlockEvents == value)
			return;

		m_BlockEvents = value;
	}

	void ImGuiLayer::BeginWindowCollection() {
		m_AnyWindowFocusedOrHovered = false;
	}

	void ImGuiLayer::RegisterWindowState(bool isFocused, bool isHovered) {
		if (isFocused || isHovered)
			m_AnyWindowFocusedOrHovered = true;
	}

	void ImGuiLayer::EndWindowCollection() {
		SetBlockEvents(!m_AnyWindowFocusedOrHovered);
	}

}