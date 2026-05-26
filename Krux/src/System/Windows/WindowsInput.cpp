#include "krxpch.h"

#include "Krux/Core/Application.h"
#include "Krux/Core/Input.h"

#include "GLFW/glfw3.h"

#if KRX_SYS_WINDOWS

namespace Krux {

	bool Input::IsKeyPressed(Key key) {
		GLFWwindow* window = (GLFWwindow*)Application::Instance()->GetWindow()->GetNativeWindow();
		int state = glfwGetKey(window, (int)key);
		return state == GLFW_PRESS;
	}

	bool Input::IsMouseButtonPressed(Mouse mouseButton) {
		GLFWwindow* window = (GLFWwindow*)Application::Instance()->GetWindow()->GetNativeWindow();
		int state = glfwGetMouseButton(window, (int)mouseButton);
		return state == GLFW_PRESS;
	}

	void Input::GetMousePosition(double& xpos, double& ypos) {
		GLFWwindow* window = (GLFWwindow*)Application::Instance()->GetWindow()->GetNativeWindow();
		glfwGetCursorPos(window, &xpos, &ypos);
	}

	void Input::SetCursorInputMode(CursorInputMode mode) {
		GLFWwindow* window = (GLFWwindow*)Application::Instance()->GetWindow()->GetNativeWindow();
		glfwSetInputMode(window, GLFW_CURSOR, (int)mode);
	}

}

#endif