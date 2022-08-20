#pragma once

#include "Core.h"
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

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		void OnEvent(Event& e);

	private:
		bool OnWindowClose(WindowCloseEvent& e);

	private:
		bool m_Running;
		LayerStack m_LayerStack;
	};

	Application* CreateApplication();
}

