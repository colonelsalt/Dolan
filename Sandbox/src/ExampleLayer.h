#pragma once

#include "Dolan.h"

class ExampleLayer : public Dolan::Layer
{
public:
	ExampleLayer();
	virtual ~ExampleLayer() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate(Dolan::Timestep ts) override;
	virtual void OnImGuiRender() override;
	void OnEvent(Dolan::Event& e) override;
private:
	Dolan::ShaderLibrary m_ShaderLibrary;
	Dolan::Ref<Dolan::Shader> m_Shader;
	Dolan::Ref<Dolan::VertexArray> m_VertexArray;

	Dolan::Ref<Dolan::Shader> m_FlatColorShader;
	Dolan::Ref<Dolan::VertexArray> m_SquareVa;

	Dolan::Ref<Dolan::Texture2d> m_Texture, m_ChernoLogoTexture;

	Dolan::OrthoCamController m_CameraController;
	glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };
};