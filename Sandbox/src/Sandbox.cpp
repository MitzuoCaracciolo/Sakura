#include "Sakura.h"

class Sandbox : public Sakura::Application
{
public:
	Sandbox()
	{

	}

	~Sandbox()
	{

	}
};

Sakura::Application* Sakura::CreateApplication()
{
	return new Sandbox();
}