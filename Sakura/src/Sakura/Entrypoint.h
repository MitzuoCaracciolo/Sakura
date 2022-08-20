#pragma once

extern Sakura::Application* Sakura::CreateApplication();

#ifdef SAKURA_PLATFORM_WINDOWS

#include <Windows.h>
#include <stdio.h>

int APIENTRY WinMain(_In_     HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_     LPSTR    lpCmdLine,
	_In_     int       nCmdShow)
{
	AllocConsole();
	FILE* fp;
	freopen_s(&fp, "CONOUT$", "w", stdout);
	freopen_s(&fp, "CONOUT$", "w", stderr);
	freopen_s(&fp, "CONIN$", "r", stdin);

	Sakura::Log::Init();
	SAKURA_CORE_WARN("Initialized Logger!");
	SAKURA_INFO("Hello Logger!");

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