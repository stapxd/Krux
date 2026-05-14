#include "krxpch.h"
#include "LayerStack.h"

namespace Krux {
	LayerStack::~LayerStack()
	{
		std::scoped_lock lock(m_LayerStackMutex);
		for (auto layer : m_LayerStack) {
			layer->OnDetach();
		}
	}

	void LayerStack::PushLayer(Layer* layer)
	{
		std::scoped_lock lock(m_LayerStackMutex);
		m_LayerStack.emplace(m_LayerStack.begin() + m_PushLayerIndex, layer);
		m_PushLayerIndex += 1;
	}

	void LayerStack::PopLayer(Layer* layer)
	{
		Ref<Layer> layerToDetach = nullptr;
		{
			std::scoped_lock lock(m_LayerStackMutex);
			auto it = std::find(m_LayerStack.begin(), m_LayerStack.begin() + m_PushLayerIndex, layer);
			if (it != m_LayerStack.begin() + m_PushLayerIndex) {
				layerToDetach = *it;
				m_LayerStack.erase(it);
				m_PushLayerIndex--;
			}
		}
		
		if (layerToDetach) {
			layerToDetach->OnDetach();
		}
	}

	void LayerStack::PushOverlay(Layer* overlay)
	{
		std::scoped_lock lock(m_LayerStackMutex);
		m_LayerStack.push_back(overlay);
	}
	void LayerStack::PopOverlay(Layer* overlay)
	{
		Ref<Layer> overlayToDetach = nullptr;
		{
			std::scoped_lock lock(m_LayerStackMutex);
			auto it = std::find(m_LayerStack.begin() + m_PushLayerIndex, m_LayerStack.end(), overlay);
			if (it != m_LayerStack.end()) {
				overlayToDetach = *it;
				m_LayerStack.erase(it);
			}
		}

		if (overlayToDetach) {
			overlayToDetach->OnDetach();
		}
	}
}