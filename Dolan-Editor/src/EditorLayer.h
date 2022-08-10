#pragma once

#include "Dolan.h"

namespace Dolan {

	class EditorLayer : public Layer
	{
	public:
		EditorLayer();
		virtual ~EditorLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		void OnUpdate(Timestep ts) override;
		virtual void OnImGuiRender() override;
		void OnEvent(Event& e) override;
	private:
		OrthoCamController m_CameraController;

		// Temporary
		Ref<VertexArray> m_SquareVa;
		Ref<Shader> m_FlatColorShader;
		Ref<FrameBuffer> m_Framebuffer;
		
		Ref<Texture2d> m_CheckerboardTexture;

		bool m_IsViewportFocused = false, m_IsViewportHovered = false;

		glm::vec2 m_ViewportSize = { 1280.0f,720.0f };

		glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };
	};
}