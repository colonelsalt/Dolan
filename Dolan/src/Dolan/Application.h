#pragma once

#include "Core.h"
#include "Window.h"
#include "Dolan/LayerStack.h"
#include "Events/Event.h"
#include "Events/ApplicationEvent.h"

#include "Dolan/ImGui/ImGuiLayer.h"

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

		inline Window& GetWindow() const { return *m_Window; }
		inline static Application& Get() { return *s_Instance; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;

		static Application* s_Instance;
	};

	// Will be implemented in client application
	Application* CreateApplication();

}
