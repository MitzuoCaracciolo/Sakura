#pragma once

#include "Sakura/Core.h"
#include "Sakura/Window.h"

#include "Sakura/Layer.h"
#include "Sakura/LayerStack.h"

#include "Sakura/Events/Event.h"
#include "Events/WindowEvents.h"


namespace Sakura
{
	class Application
	{
	public:
		Application();
		~Application();

		void Run();
		void OnEvent(Event& e);

		void PushLayer(std::unique_ptr<Layer> layer) { m_LayerStack.PushLayer(std::move(layer)); }
		void PushOverlay(std::unique_ptr<Layer> overlay) { m_LayerStack.PushOverlay(std::move(overlay)); }

		template<typename T, typename... Args>
		void PushLayer(Args&& ...args)
		{
			m_LayerStack.PushLayer<T>(std::forward<Args>(args)...);
		}

		template<typename T, typename... Args>
		void PushOverlay(Args&& ...args)
		{
			m_LayerStack.PushOverlay<T>(std::forward<Args>(args)...);
		}

		Window& GetWindow() { return *m_Window.get(); }

	private:
		bool OnWindowClose(WindowCloseEvent& e);

	private:
		bool m_Running;
		LayerStack m_LayerStack;
		std::unique_ptr<Window> m_Window;
	};

	// Client-Side
	Application* CreateApplication();
}

