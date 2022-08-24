#include "skpch.h"
#include "Application.h"

namespace Sakura
{
	Application::Application()
		: m_Running(true)
	{
		WindowSpecification spec = { };
		spec.Title = "Sakura Engine";
		spec.EventCallback = SAKURA_BIND_EVENT_FN(Application::OnEvent);

		m_Window = Window::Create(spec);
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		auto& graphics = m_Window->GetContext();
		while (m_Running)
		{
			graphics.ClearBackBuffer(0.1f, 0.105f, 0.11f);

			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();

			m_Window->OnUpdate();
		}
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* overlay)
	{
		m_LayerStack.PushOverlay(overlay);
		overlay	->OnAttach();
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(SAKURA_BIND_EVENT_FN(Application::OnWindowClose));

		for (auto it = m_LayerStack.rbegin(); it != m_LayerStack.rend(); ++it)
		{
			if (e.Handled)
				break;
			(*it)->OnEvent(e);
		}
	}
	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}
}
