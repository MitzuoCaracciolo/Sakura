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

		template<typename T, typename... Args>
		void PushLayer(Args&& ...args)
		{
			static_assert(std::is_base_of<Layer, T>::value, "Pushed type is not subclass of Layer");
			std::unique_ptr<T> layer = std::make_unique<T>(std::forward<Args>(args)...);
			layer->OnAttach();
			m_Layers.emplace(m_Layers.begin() + m_LayerInsertIndex, std::move(layer));
			m_LayerInsertIndex++;
		}

		template<typename T, typename... Args>
		void PushOverlay(Args&& ...args)
		{
			static_assert(std::is_base_of<Layer, T>::value, "Pushed type is not subclass of Layer");
			std::unique_ptr<T> overlay = std::make_unique<T>(std::forward<Args>(args)...);
			overlay->OnAttach();
			m_Layers.emplace_back(std::move(overlay));
		}

		std::vector<std::unique_ptr<Layer>>::iterator begin() { return m_Layers.begin(); }
		std::vector<std::unique_ptr<Layer>>::iterator end() { return m_Layers.end(); }

		std::vector<std::unique_ptr<Layer>>::reverse_iterator rbegin() { return m_Layers.rbegin(); }
		std::vector<std::unique_ptr<Layer>>::reverse_iterator rend() { return m_Layers.rend(); }

	private:
		uint32 m_LayerInsertIndex = 0;
		std::vector<std::unique_ptr<Layer>> m_Layers;
	};
}

