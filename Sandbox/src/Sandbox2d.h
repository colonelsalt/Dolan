#pragma once

#include "Dolan.h"

class Sandbox2d : public Dolan::Layer
{
public:
	Sandbox2d();
	virtual ~Sandbox2d() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;
	void OnUpdate(Dolan::Timestep ts) override;
	virtual void OnImGuiRender() override;
	void OnEvent(Dolan::Event& e) override;
private:
	Dolan::OrthoCamController m_CameraController;

	// Temporary
	Dolan::Ref<Dolan::VertexArray> m_SquareVa;
	Dolan::Ref<Dolan::Shader> m_FlatColorShader;
	
	Dolan::Ref<Dolan::Texture2d> m_CheckerboardTexture;

	glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };
};