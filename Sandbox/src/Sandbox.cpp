#include "Sakura.h"
#include "Sakura/Entrypoint.h"

#include "TestLayer.h"

class Sandbox : public Sakura::Application
{
public:
	Sandbox()
	{
		TestLayer* layer = new TestLayer(m_Window->GetContext());
		m_LayerStack.PushLayer(layer);
	}

	~Sandbox()
	{

	}
};

Sakura::Application* Sakura::CreateApplication()
{
	return new Sandbox();
}