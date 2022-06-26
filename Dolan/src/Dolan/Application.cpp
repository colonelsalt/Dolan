#include "Application.h"

#include "Dolan/Events/ApplicationEvent.h"
#include "Dolan/Log.h"

namespace Dolan {

	Application::Application()
	{

	}

	Application::~Application()
	{

	}

	void Application::Run()
	{
		WindowResizeEvent e(1280, 720);
		DN_TRACE(e);

		while (true);
	}

}