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

	protected:
		bool OnWindowClose(WindowCloseEvent& e);

	protected:
		bool m_Running;
		LayerStack m_LayerStack;
		std::unique_ptr<Window> m_Window;
	};

	// Client-Side
	Application* CreateApplication();
}

