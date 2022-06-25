#pragma once

#ifdef DN_PLATFORM_WINDOWS

extern Dolan::Application* Dolan::CreateApplication();

int main(int argc, char** argv)
{
	Dolan::Application* app= Dolan::CreateApplication();
	app->Run();
	delete app;
}

#endif // DN_PLATFORM_WINDOWS

