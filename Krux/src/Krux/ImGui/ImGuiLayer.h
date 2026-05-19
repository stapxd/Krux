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

		void SetBlockEvents(bool value);
		void Begin();
		void End();
	private:
		bool m_BlockEvents = true;
	};

}

