#pragma once

#include "Sakura/Core.h"
#include "Sakura/Layer.h"

#include <vector>
#include <memory>

namespace Sakura
{
	class LayerStack
	{
	public:
		void PushLayer(std::unique_ptr<Layer> layer);
		void PushOverlay(std::unique_ptr<Layer> overlay);

		std::vector<std::unique_ptr<Layer>>::iterator begin() { return m_Layers.begin(); }
		std::vector<std::unique_ptr<Layer>>::iterator end() { return m_Layers.end(); }

		std::vector<std::unique_ptr<Layer>>::reverse_iterator rbegin() { return m_Layers.rbegin(); }
		std::vector<std::unique_ptr<Layer>>::reverse_iterator rend() { return m_Layers.rend(); }

	private:
		uint32 m_LayerInsertIndex = 0;
		std::vector<std::unique_ptr<Layer>> m_Layers;
	};
}

