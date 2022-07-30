#pragma once

#include "Dolan/Core/Core.h"

#ifdef DN_PLATFORM_WINDOWS

extern Dolan::Application* Dolan::CreateApplication();

int main(int argc, char** argv)
{
	Dolan::Log::Init();
	DN_CORE_WARN("Log initialised!");
	int a = 69;
	DN_INFO("Hello from client; var={0}", a);

	Dolan::Application* app= Dolan::CreateApplication();
	app->Run();
	delete app;
}

#endif // DN_PLATFORM_WINDOWS
