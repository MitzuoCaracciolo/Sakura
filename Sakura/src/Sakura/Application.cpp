#include "skpch.h"
#include "Application.h"

namespace Sakura
{
	Application::Application()
		: m_Running(true)
	{
		WindowSpecification windowSpec = { };
		windowSpec.Title = "Sakura Engine";
		windowSpec.EventCallback = SAKURA_BIND_EVENT_FN(Application::OnEvent);

		m_Window = Window::Create(windowSpec);
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		auto graphics = m_Window->GetContext();
		while (m_Running)
		{
			graphics->ClearBackBuffer(0.1f, 0.105f, 0.11f);

			m_Window->OnUpdate();

			for (const auto& layer : m_LayerStack)
				layer->OnUpdate();

			graphics->SwapBackBuffer();
		}
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
	void Application::PushLayer(std::unique_ptr<Layer> layer)
	{
		layer->OnAttach();
		m_LayerStack.PushLayer(std::move(layer));
	}

	void Application::PushOverlay(std::unique_ptr<Layer> overlay)
	{
		overlay->OnAttach();
		m_LayerStack.PushOverlay(std::move(overlay));
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}
}
