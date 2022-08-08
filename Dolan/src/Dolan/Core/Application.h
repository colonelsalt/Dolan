#pragma once

#include "Dolan/Core/Base.h"
#include "Dolan/Core/Window.h"
#include "Dolan/Core/LayerStack.h"
#include "Dolan/Events/Event.h"
#include "Dolan/Events/ApplicationEvent.h"

#include "Dolan/Core/Timestep.h"

#include "Dolan/ImGui/ImGuiLayer.h"

namespace Dolan {
	class Application
	{
	public:
		Application(const std::string& name = "Dolan Engine");
		virtual ~Application();
		
		void Run();
		
		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		void Close();

		inline Window& GetWindow() const { return *m_Window; }
		inline static Application& Get() { return *s_Instance; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);

		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		bool m_Minimized = false;
		LayerStack m_LayerStack;
		float m_LastFrameTime = 0.0f;
	private:
		static Application* s_Instance;
	};

	// Will be implemented in client application
	Application* CreateApplication();

}
