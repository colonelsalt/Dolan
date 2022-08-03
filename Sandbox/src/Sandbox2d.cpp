#include "Sandbox2d.h"

#include <imgui/imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Platform/OpenGL/OpenGlShader.h"


Sandbox2d::Sandbox2d()
	: Layer("Sandbox2d"), m_CameraController(1280.0f / 720.0f)
{
}

void Sandbox2d::OnAttach()
{
	DN_PROFILE_FUNCTION();

	m_CheckerboardTexture = Dolan::Texture2d::Create("assets/textures/Checkerboard.png");
}

void Sandbox2d::OnDetach()
{
	DN_PROFILE_FUNCTION();
}

void Sandbox2d::OnUpdate(Dolan::Timestep ts)
{
	DN_PROFILE_FUNCTION();
	m_CameraController.OnUpdate(ts);

	Dolan::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
	Dolan::RenderCommand::Clear();
	
	Dolan::Renderer2d::BeginScene(m_CameraController.GetCamera());

	Dolan::Renderer2d::DrawRotatedQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, glm::radians(-45.0f), { 0.8f, 0.2f, 0.3f, 1.0f });
	Dolan::Renderer2d::DrawQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, { 0.2f, 0.3f, 0.8f, 1.0f });
	Dolan::Renderer2d::DrawQuad({ 0.2f, 0.5f, -0.1f }, { 10.0f, 10.0f }, m_CheckerboardTexture, 10.0f);

	Dolan::Renderer2d::EndScene();
	
}

void Sandbox2d::OnImGuiRender()
{
	DN_PROFILE_FUNCTION();
	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Square colour", glm::value_ptr(m_SquareColor));
	
	ImGui::End();
}

void Sandbox2d::OnEvent(Dolan::Event& e)
{
	m_CameraController.OnEvent(e);
}
