#include <Dolan.h>
#include <Dolan/Core/EntryPoint.h>

#include <imgui/imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Sandbox2d.h"

class ExampleLayer : public Dolan::Layer
{
public:
	ExampleLayer()
		: Dolan::Layer("ExampleLayer"), m_CameraController(1280.0f / 720.0f)
	{
		m_VertexArray = Dolan::VertexArray::Create();

		float vertices[7 * 3] = {
			-0.5f, -0.5f, 0.0f,		0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f,		0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f,		0.8f, 0.8f, 0.2f, 1.0f
		};

		Dolan::Ref<Dolan::VertexBuffer> vertexBuffer = Dolan::VertexBuffer::Create(vertices, sizeof(vertices));
		Dolan::BufferLayout layout = {
			{ Dolan::ShaderDataType::Float3, "a_Position" },
			{ Dolan::ShaderDataType::Float4, "a_Color" }
		};
		vertexBuffer->SetLayout(layout);

		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[3] = { 0, 1, 2 };
		Dolan::Ref<Dolan::IndexBuffer> indexBuffer = Dolan::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_SquareVa = Dolan::VertexArray::Create();

		float squareVertices[5 * 4] = {
			-0.5f, -0.5f, 0.0f,		0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f,		1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f,		1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f,		0.0f, 1.0f
		};

		Dolan::Ref<Dolan::VertexBuffer> squareVb = Dolan::VertexBuffer::Create(squareVertices, sizeof(squareVertices));
		squareVb->SetLayout({
			{ Dolan::ShaderDataType::Float3, "a_Position" },
			{ Dolan::ShaderDataType::Float2, "a_TexCoord" }
			});
		m_SquareVa->AddVertexBuffer(squareVb);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		Dolan::Ref<Dolan::IndexBuffer> squareIb = Dolan::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t));
		m_SquareVa->SetIndexBuffer(squareIb);

		std::string vertexSrc = R"(
			#version 330 core
				
			layout(location = 0) in vec3 a_Position;		
			layout(location = 1) in vec4 a_Color;		

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core
				
			layout(location = 0) out vec4 color;			

			in vec3 v_Position;
			in vec4 v_Color;

			void main()
			{
				color = vec4(v_Position + 0.5, 1.0);
				color = v_Color;
			}
		)";

		m_Shader = Dolan::Shader::Create("VertexPosColor", vertexSrc, fragmentSrc);

		std::string flatColorShaderVertSrc = R"(
			#version 330 core
				
			layout(location = 0) in vec3 a_Position;		

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;			

			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}
		)";

		std::string flatColorShaderFragSrc = R"(
			#version 330 core
				
			layout(location = 0) out vec4 color;

			in vec3 v_Position;

			uniform vec3 u_Color;

			void main()
			{
				color = vec4(u_Color, 1.0);
			}
		)";
		m_FlatColorShader = Dolan::Shader::Create("FlatColor", flatColorShaderVertSrc, flatColorShaderFragSrc);

		Dolan::Ref<Dolan::Shader> textureShader = m_ShaderLibrary.Load("assets/shaders/Texture.glsl");

		m_Texture = Dolan::Texture2d::Create("assets/textures/Checkerboard.png");
		m_ChernoLogoTexture = Dolan::Texture2d::Create("assets/textures/ChernoLogo.png");

		textureShader->Bind();
		textureShader->SetInt("u_Texture", 0);

	}

	void OnUpdate(Dolan::Timestep ts) override
	{
		m_CameraController.OnUpdate(ts);

		Dolan::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Dolan::RenderCommand::Clear();

		Dolan::Renderer::BeginScene(m_CameraController.GetCamera());
		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f, 0.1f, 0.1f));

		m_FlatColorShader->Bind();
		m_FlatColorShader->SetFloat3("u_Color", m_SquareColor);

		for (int y = 0; y < 20; y++)
		{
			for (int x = 0; x < 20; x++)
			{
				glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;

				Dolan::Renderer::Submit(m_FlatColorShader, m_SquareVa, transform);
			}
		}

		auto textureShader = m_ShaderLibrary.Get("Texture");

		m_Texture->Bind();
		Dolan::Renderer::Submit(textureShader, m_SquareVa, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
		
		m_ChernoLogoTexture->Bind();
		Dolan::Renderer::Submit(textureShader, m_SquareVa,glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

		Dolan::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("Square colour", glm::value_ptr(m_SquareColor));
		ImGui::End();
	}

	void OnEvent(Dolan::Event& e) override
	{
		m_CameraController.OnEvent(e);
	}

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

class Sandbox : public Dolan::Application
{
public:
	Sandbox()
	{
		// PushLayer(new ExampleLayer());
		PushLayer(new Sandbox2d());
	}

	~Sandbox()
	{

	}
};

Dolan::Application* Dolan::CreateApplication()
{
	return new Sandbox();
}