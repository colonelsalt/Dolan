#include "Sandbox2d.h"

#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Platform/OpenGL/OpenGlShader.h"

Sandbox2d::Sandbox2d()
	: Layer("Sandbox2d"), m_CameraController(1280.0f / 720.0f)
{
}

void Sandbox2d::OnAttach()
{
	m_SquareVa = Dolan::VertexArray::Create();

	float squareVertices[3 * 4] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.5f,  0.5f, 0.0f,
		-0.5f,  0.5f, 0.0f,
	};

	Dolan::Ref<Dolan::VertexBuffer> squareVb;
	squareVb.reset(Dolan::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
	squareVb->SetLayout({
		{ Dolan::ShaderDataType::Float3, "a_Position" }
	});
	m_SquareVa->AddVertexBuffer(squareVb);

	uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
	Dolan::Ref<Dolan::IndexBuffer> squareIb;
	squareIb.reset(Dolan::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
	m_SquareVa->SetIndexBuffer(squareIb);

	m_FlatColorShader = Dolan::Shader::Create("assets/shaders/FlatColor.glsl");
}

void Sandbox2d::OnDetach()
{

}

void Sandbox2d::OnUpdate(Dolan::Timestep ts)
{
	m_CameraController.OnUpdate(ts);

	Dolan::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
	Dolan::RenderCommand::Clear();

	Dolan::Renderer::BeginScene(m_CameraController.GetCamera());

	std::dynamic_pointer_cast<Dolan::OpenGlShader>(m_FlatColorShader)->Bind();
	std::dynamic_pointer_cast<Dolan::OpenGlShader>(m_FlatColorShader)->UploadUniformFloat4("u_Color", m_SquareColor);

	Dolan::Renderer::Submit(m_FlatColorShader, m_SquareVa, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

	Dolan::Renderer::EndScene();
}

void Sandbox2d::OnImGuiRender()
{
	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Square colour", glm::value_ptr(m_SquareColor));
	ImGui::End();
}

void Sandbox2d::OnEvent(Dolan::Event& e)
{
	m_CameraController.OnEvent(e);
}
