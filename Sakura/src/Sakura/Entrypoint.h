#pragma once

extern Sakura::Application* Sakura::CreateApplication();

#ifdef SAKURA_PLATFORM_WINDOWS

#include <Windows.h>
#include <stdio.h>

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, INT nCmdShow)
{
	AllocConsole();
	FILE* fp;
	freopen_s(&fp, "CONOUT$", "w", stdout);
	freopen_s(&fp, "CONOUT$", "w", stderr);
	freopen_s(&fp, "CONIN$", "r", stdin);

	Sakura::Application* app = Sakura::CreateApplication();
	app->Run();
	delete app;
	return 0;
}

#else

int main(int argc, char** argv)
{

}

#endif