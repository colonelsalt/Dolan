#include "dnpch.h"
#include "OrthoCamController.h"

#include "Dolan/Core/KeyCodes.h"
#include "Dolan/Core/Input.h"

namespace Dolan {

	OrthoCamController::OrthoCamController(float aspect, bool rotation)
		: m_Aspect(aspect), m_RotationEnabled(rotation),
		m_Camera(-m_Aspect * m_ZoomLevel, m_Aspect * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel)
	{

	}

	void OrthoCamController::OnUpdate(Timestep ts)
	{
		if (Input::IsKeyPressed(DN_KEY_A))
			m_CameraPos.x -= m_CameraTranslateSpeed * ts;
		else if (Input::IsKeyPressed(DN_KEY_D))
			m_CameraPos.x += m_CameraTranslateSpeed * ts;

		if (Input::IsKeyPressed(DN_KEY_W))
			m_CameraPos.y += m_CameraTranslateSpeed * ts;
		else if (Input::IsKeyPressed(DN_KEY_S))
			m_CameraPos.y -= m_CameraTranslateSpeed * ts;

		if (m_RotationEnabled)
		{
			if (Input::IsKeyPressed(DN_KEY_Q))
				m_CameraRot += m_CameraRotSpeed * ts;
			if (Input::IsKeyPressed(DN_KEY_E))
				m_CameraRot -= m_CameraRotSpeed * ts;
			
			m_Camera.SetRotation(m_CameraRot);
		}

		m_Camera.SetPosition(m_CameraPos);

		m_CameraTranslateSpeed = m_ZoomLevel;
	}

	void OrthoCamController::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<MouseScrolledEvent>(DN_BIND_EVENT_FN(OrthoCamController::OnMouseScrolled));
		dispatcher.Dispatch<WindowResizeEvent>(DN_BIND_EVENT_FN(OrthoCamController::OnWindowResized));
	}

	bool OrthoCamController::OnMouseScrolled(MouseScrolledEvent& e)
	{
		m_ZoomLevel -= e.GetYOffset() * 0.25f;
		m_ZoomLevel = std::max(m_ZoomLevel, 0.25f);
		m_Camera.SetProjection(-m_Aspect * m_ZoomLevel, m_Aspect * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
		return false;
	}

	bool OrthoCamController::OnWindowResized(WindowResizeEvent& e)
	{
		m_Aspect = (float)e.GetWidth() / (float)e.GetHeight();
		m_Camera.SetProjection(-m_Aspect * m_ZoomLevel, m_Aspect * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
		return false;
	}

}