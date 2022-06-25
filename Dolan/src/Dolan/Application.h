#pragma once

#include "Core.h"

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
