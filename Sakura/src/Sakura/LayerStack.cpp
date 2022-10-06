#include "skpch.h"
#include "LayerStack.h"


void Sakura::LayerStack::PushLayer(std::unique_ptr<Layer> layer)
{
	m_Layers.emplace(m_Layers.begin() + m_LayerInsertIndex, std::move(layer));
	m_LayerInsertIndex++;
}

void Sakura::LayerStack::PushOverlay(std::unique_ptr<Layer> overlay)
{
	m_Layers.emplace_back(std::move(overlay));
}
