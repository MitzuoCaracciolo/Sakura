#include "Sakura.h"
#include "Sakura/Entrypoint.h"

#include "TestLayer.h"
#include "TestMeshLayer.h"

class Sandbox : public Sakura::Application
{
public:
	Sandbox()
	{
		//PushLayer<TestLayer>(GetWindow());
		PushLayer<TestMeshLayer>(GetWindow());
	}

	~Sandbox()
	{

	}
};

Sakura::Application* Sakura::CreateApplication()
{
	return new Sandbox();
}