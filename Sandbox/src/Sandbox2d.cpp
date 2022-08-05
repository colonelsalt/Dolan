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

	Dolan::Renderer2d::ResetStats();

	Dolan::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
	Dolan::RenderCommand::Clear();
	
	static float rotation = 0.0f;
	rotation += ts * 50.0f;

	Dolan::Renderer2d::BeginScene(m_CameraController.GetCamera());

	Dolan::Renderer2d::DrawRotatedQuad({ 1.0f, 0.0f }, { 0.8f, 0.8f }, -45.0f, { 0.8f, 0.2f, 0.3f, 1.0f });
	Dolan::Renderer2d::DrawQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, { 0.8f, 0.2f, 0.3f, 1.0f });
	Dolan::Renderer2d::DrawQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, { 0.2f, 0.3f, 0.8f, 1.0f });
	Dolan::Renderer2d::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 20.0f, 20.0f }, m_CheckerboardTexture, 10.0f);
	Dolan::Renderer2d::DrawRotatedQuad({ -2.0f, 0.0f, 0.0f }, { 1.0f, 1.0f }, rotation, m_CheckerboardTexture, 20.0f);

	Dolan::Renderer2d::EndScene();

	Dolan::Renderer2d::BeginScene(m_CameraController.GetCamera());
	for (float y = -5.0f; y < 5.0f; y += 0.5f)
	{
		for (float x = -5.0f; x < 5.0f; x += 0.5f)
		{
			glm::vec4 color = { (x + 5.0f) / 10.0f, 0.4f, (y + 5.0f) / 10.0f, 0.7f };
			Dolan::Renderer2d::DrawQuad({ x, y }, { 0.45f, 0.45f }, color);
		}
	}
	Dolan::Renderer2d::EndScene();

}

void Sandbox2d::OnImGuiRender()
{
	DN_PROFILE_FUNCTION();
	ImGui::Begin("Settings");

	Dolan::Renderer2d::Statistics stats = Dolan::Renderer2d::GetStats();

	ImGui::Text("Renderer2d Stats:");
	ImGui::Text("Draw calls: %d", stats.DrawCalls);
	ImGui::Text("Quads: %d", stats.QuadCount);
	ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
	ImGui::Text("Indices: %d", stats.GetTotalIndexCount());

	ImGui::ColorEdit4("Square colour", glm::value_ptr(m_SquareColor));
	
	ImGui::End();
}

void Sandbox2d::OnEvent(Dolan::Event& e)
{
	m_CameraController.OnEvent(e);
}
