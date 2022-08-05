#pragma once

#include "Dolan/Core/Base.h"

#ifdef DN_PLATFORM_WINDOWS

extern Dolan::Application* Dolan::CreateApplication();

int main(int argc, char** argv)
{
	Dolan::Log::Init();
	
	DN_PROFILE_BEGIN_SESSION("Startup", "DolanProfile-Startup.json");
	Dolan::Application* app= Dolan::CreateApplication();
	DN_PROFILE_END_SESSION();

	DN_PROFILE_BEGIN_SESSION("Startup", "DolanProfile-Runtime.json");
	app->Run();
	DN_PROFILE_END_SESSION();

	DN_PROFILE_BEGIN_SESSION("Startup", "DolanProfile-Shutdown.json");
	delete app;
	DN_PROFILE_END_SESSION();
}

#endif // DN_PLATFORM_WINDOWS
