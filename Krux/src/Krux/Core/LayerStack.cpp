#include "krxpch.h"
#include "LayerStack.h"

namespace Krux {
	LayerStack::~LayerStack()
	{
		for (auto layer : m_LayerStack) {
			layer->OnDetach();
			delete layer;
		}
	}

	void LayerStack::PushLayer(Layer* layer)
	{
		m_LayerStack.emplace(m_LayerStack.begin() + m_PushLayerIndex, layer);
		m_PushLayerIndex += 1;
	}

	void LayerStack::PopLayer(Layer* layer)
	{
		auto it = std::find(m_LayerStack.begin(), m_LayerStack.begin() + m_PushLayerIndex, layer);
		if (it != m_LayerStack.begin() + m_PushLayerIndex) {
			(*it)->OnDetach();
			m_LayerStack.erase(it);
			m_PushLayerIndex--;
		}
	}

	void LayerStack::PushOverlay(Layer* overlay)
	{
		m_LayerStack.push_back(overlay);
	}
	void LayerStack::PopOverlay(Layer* overlay)
	{
		auto it = std::find(m_LayerStack.begin() + m_PushLayerIndex, m_LayerStack.end(), overlay);
		if (it != m_LayerStack.end()) {
			(*it)->OnDetach();
			m_LayerStack.erase(it);
		}
	}
}