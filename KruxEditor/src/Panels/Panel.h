#pragma once

#include "Krux/Core/UUID.h"

#include <xstring>
#include <variant>

#define IMGUI_DEFINE_MATH_OPERATORS
#include <imgui.h>

namespace Krux {

	class Panel {
	public:
		using PanelData = std::variant<std::monostate, uint32_t, UUID64>;

		Panel(const std::string& name);

		void OnRender(PanelData panelData = std::monostate{}, ImGuiWindowFlags flags = 0);

		virtual void RenderContent(PanelData panelData = std::monostate{}) = 0;
		virtual void PushWindowStyles() {}
		virtual void PopWindowStyles() {}

		bool IsFocused() const { return m_IsFocused; }
		bool IsHovered() const { return m_IsHovered; }

		bool* Open() { return &m_IsOpen; }

	protected:
		std::string m_Name = "";

		// Flags
		bool m_IsOpen = true;
		bool m_IsFocused = false;
		bool m_IsHovered = false;
	};

}