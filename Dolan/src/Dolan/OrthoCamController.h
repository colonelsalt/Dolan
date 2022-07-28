#pragma once

#include "Dolan/Renderer/OrthographicCamera.h"
#include "Dolan/Core/Timestep.h"

#include "Dolan/Events/ApplicationEvent.h"
#include "Dolan/Events/MouseEvent.h"

namespace Dolan {

	class OrthoCamController
	{
	public:
		OrthoCamController(float aspect, bool rotation = false);

		void OnUpdate(Timestep ts);
		void OnEvent(Event& e);

		OrthographicCamera& GetCamera() { return m_Camera; }
		const OrthographicCamera& GetCamera() const { return m_Camera; }

		float GetZoomLevel() const { return m_ZoomLevel; }
		void SetZoomLevel(float level) { m_ZoomLevel = level; }
	private:
		bool OnMouseScrolled(MouseScrolledEvent& e);
		bool OnWindowResized(WindowResizeEvent& e);
	private:
		bool m_RotationEnabled;
		float m_Aspect;
		float m_ZoomLevel = 1.0f;
		OrthographicCamera m_Camera;

		glm::vec3 m_CameraPos = { 0.0f, 0.0f, 0.0f };
		float m_CameraRot = 0.0f;

		float m_CameraTranslateSpeed = 5.0f;
		float m_CameraRotSpeed = 180.0f;
	};

}