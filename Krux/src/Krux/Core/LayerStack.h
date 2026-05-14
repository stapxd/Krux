#pragma once

#include "Ref.h"
#include "Layer.h"

#include <vector>
#include <mutex>

namespace Krux {

	class LayerStack
	{
	public:
		LayerStack() = default;
		~LayerStack();

		std::mutex& GetMutex() { return m_LayerStackMutex; }

		void PushLayer(Layer* layer);
		void PopLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
		void PopOverlay(Layer* overlay);

		auto rbegin() { return m_LayerStack.rbegin(); }
		auto rend() { return m_LayerStack.rend(); }

		auto begin() { return m_LayerStack.begin(); }
		auto end() { return m_LayerStack.end(); }

	private:
		std::vector<Ref<Layer>> m_LayerStack;
		uint32_t m_PushLayerIndex = 0;

		std::mutex m_LayerStackMutex;
	};

}

