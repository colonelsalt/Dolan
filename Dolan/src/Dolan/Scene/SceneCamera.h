#pragma once

#include "Dolan/Renderer/Camera.h"

namespace Dolan {

	class SceneCamera : public Camera
	{
	public:
		enum class ProjectionType { Perspective = 0, Orthographic = 1 };
	public:
		SceneCamera();
		virtual ~SceneCamera() = default;

		void SetOrthographic(float size, float nearClip, float farClip);
		void SetPerspective(float verticalFov, float nearClip, float farClip);

		void SetViewportSize(uint32_t width, uint32_t height);

		float GetPerspVerticalFov() const { return m_PerspectiveFov; }
		void SetPerspVerticalFov(float fov) { m_PerspectiveFov = fov; RecalculateProjection(); }
		float GetPerspNearClip() const { return m_PerspectiveNear; }
		void SetPerspNearClip(float nearClip) { m_PerspectiveNear = nearClip; RecalculateProjection(); }
		float GetPerspFarClip() const { return m_PerspectiveFar; }
		void SetPerspFarClip(float farClip) { m_PerspectiveFar = farClip; RecalculateProjection(); }

		float GetOrthographicSize() const { return m_OrthographicSize; }
		void SetOrthographicSize(float size) { m_OrthographicSize = size; RecalculateProjection(); }

		float GetOrthoNearClip() const { return m_OrthographicNear; }
		void SetOrthoNearClip(float nearClip) { m_OrthographicNear = nearClip; RecalculateProjection(); }

		float GetOrthoFarClip() const { return m_OrthographicFar; }
		void SetOrthoFarClip(float farClip) { m_OrthographicFar = farClip; RecalculateProjection(); }



		ProjectionType GetProjectionType() const { return m_ProjectionType; }
		void SetProjectionType(ProjectionType type) { m_ProjectionType = type; RecalculateProjection(); }

	private:
		void RecalculateProjection();
	private:
		ProjectionType m_ProjectionType = ProjectionType::Orthographic;

		float m_PerspectiveFov = glm::radians(45.0f);
		float m_PerspectiveNear = 0.01f, m_PerspectiveFar = 1'000.0f;
		
		float m_OrthographicSize = 10.0;
		float m_OrthographicNear = -1.0f, m_OrthographicFar = 1.0f;

		float m_Aspect = 0.0f;
	};

}