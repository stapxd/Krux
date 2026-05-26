#pragma once

#include "Krux/Core/Layer.h"

namespace Krux {

	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnEvent(Event& e) override;

		void BeginWindowCollection();
		void RegisterWindowState(bool isFocused, bool isHovered);
		void EndWindowCollection();

		void SetBlockEventsOverride(bool value);
		void SetBlockEvents(bool value);
		void Begin();
		void End();
		
	private:
		void SetColorTheme();

	private:
		bool m_BlockEvents = true;
		bool m_BlockEventsOverride = false;
		bool m_AnyWindowFocusedOrHovered = false;
	};

}

