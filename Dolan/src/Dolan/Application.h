#pragma once

#include "Core.h"
#include "Events/Event.h"

namespace Dolan {
	class DOLAN_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	// Will be implemented in client application
	Application* CreateApplication();

}
