#pragma once

#include "Krux/Core/Layer.h"

namespace Krux {

	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();

		void OnAttachWindow();
		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnEvent(Event& e) override;

		void Begin();
		void End();
	private:
		bool m_BlockEvents = true;
	};

}

