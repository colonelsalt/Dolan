#pragma once

#include "Core.h"
#include "Window.h"
#include "Dolan/LayerStack.h"
#include "Events/Event.h"
#include "Events/ApplicationEvent.h"

#include "Dolan/ImGui/ImGuiLayer.h"
#include "Dolan/Renderer/Shader.h"
#include "Dolan/Renderer/Buffer.h"
#include "Dolan/Renderer/VertexArray.h"
#include "Renderer/OrthographicCamera.h"

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

		std::shared_ptr<Shader> m_Shader;
		std::shared_ptr<VertexArray> m_VertexArray;

		std::shared_ptr<Shader> m_BlueShader;
		std::shared_ptr<VertexArray> m_SquareVa;

		OrthographicCamera m_Camera;

	private:
		static Application* s_Instance;
	};

	// Will be implemented in client application
	Application* CreateApplication();

}
