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

		void PushLayer(std::unique_ptr<Layer> layer);
		void PushOverlay(std::unique_ptr<Layer> overlay);

		template<typename T, typename... Args>
		void PushLayer(Args&& ...args)
		{
			static_assert(std::is_base_of<Layer, T>::value, "Pushed type is not subclass of Layer");
			std::unique_ptr<T> layer = std::make_unique<T>(std::forward<Args>(args)...);
			PushLayer(std::move(layer));
		}

		template<typename T, typename... Args>
		void PushOverlay(Args&& ...args)
		{
			static_assert(std::is_base_of<Layer, T>::value, "Pushed type is not subclass of Layer");
			std::unique_ptr<T> overlay = std::make_unique<T>(std::forward<Args>(args)...);
			PushOverlay(std::move(overlay));
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

