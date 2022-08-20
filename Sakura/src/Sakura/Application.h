#pragma once

#include "Core.h"

namespace Sakura
{
	class Application
	{
	public:
		Application();
		~Application();

		void Run();

	private:
		bool m_Running;
	};

	Application* CreateApplication();
}

