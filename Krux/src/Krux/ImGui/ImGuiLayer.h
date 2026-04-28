#pragma once

#include "Krux/Core/Layer.h"

namespace Krux {

	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;

		void Begin();
		void End();
	};

}

