#pragma once

#include "Core.h"

namespace Sakura
{
	class SAKURA_API Application
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

