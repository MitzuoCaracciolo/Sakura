#include "Sakura.h"
#include "Sakura/Entrypoint.h"

#include "TestLayer.h"

class Sandbox : public Sakura::Application
{
public:
	Sandbox()
	{
		m_LayerStack.PushLayer<TestLayer>(m_Window->GetContext());
	}

	~Sandbox()
	{

	}
};

Sakura::Application* Sakura::CreateApplication()
{
	return new Sandbox();
}