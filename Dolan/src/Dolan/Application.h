#pragma once

#include "Core.h"
#include "Window.h"
#include "Dolan/LayerStack.h"
#include "Events/Event.h"
#include "Events/ApplicationEvent.h"


namespace Dolan {
	class DOLAN_API Application
	{
	public:
		Application();
		virtual ~Application();
		
		void Run();
		
		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
		LayerStack m_LayerStack;
	};

	// Will be implemented in client application
	Application* CreateApplication();

}
