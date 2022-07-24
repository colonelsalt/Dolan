#pragma once

#include "Core.h"
#include "Window.h"
#include "Dolan/LayerStack.h"
#include "Events/Event.h"
#include "Events/ApplicationEvent.h"

#include "Dolan/Core/Timestep.h"

#include "Dolan/ImGui/ImGuiLayer.h"

namespace Dolan {
	class Application
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
		float m_LastFrameTime = 0.0f;
	private:
		static Application* s_Instance;
	};

	// Will be implemented in client application
	Application* CreateApplication();

}
