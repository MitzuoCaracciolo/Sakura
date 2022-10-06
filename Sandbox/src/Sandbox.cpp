#include "Sakura.h"
#include "Sakura/Entrypoint.h"

#include "TestLayer.h"

class Sandbox : public Sakura::Application
{
public:
	Sandbox()
	{
		PushLayer<TestLayer>(GetWindow());
	}

	~Sandbox()
	{

	}
};

Sakura::Application* Sakura::CreateApplication()
{
	return new Sandbox();
}