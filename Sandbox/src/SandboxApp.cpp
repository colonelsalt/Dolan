#include <Dolan.h>

#include "imgui/imgui.h"

class ExampleLayer : public Dolan::Layer
{
public:
	ExampleLayer()
		: Dolan::Layer("ExampleLayer"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPos(0.0f)
	{
		m_VertexArray.reset(Dolan::VertexArray::Create());

		float vertices[7 * 3] = {
			-0.5f, -0.5f, 0.0f,		0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f,		0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f,		0.8f, 0.8f, 0.2f, 1.0f
		};

		std::shared_ptr<Dolan::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Dolan::VertexBuffer::Create(vertices, sizeof(vertices)));
		Dolan::BufferLayout layout = {
			{ Dolan::ShaderDataType::Float3, "a_Position" },
			{ Dolan::ShaderDataType::Float4, "a_Color" }
		};
		vertexBuffer->SetLayout(layout);

		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[3] = { 0, 1, 2 };
		std::shared_ptr<Dolan::IndexBuffer> indexBuffer;
		indexBuffer.reset(Dolan::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_SquareVa.reset(Dolan::VertexArray::Create());

		float squareVertices[3 * 4] = {
			-0.75f, -0.75f, 0.0f,
			 0.75f, -0.75f, 0.0f,
			 0.75f,  0.75f, 0.0f,
			-0.75f,  0.75f, 0.0f,
		};

		std::shared_ptr<Dolan::VertexBuffer> squareVb;
		squareVb.reset(Dolan::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		squareVb->SetLayout({
			{ Dolan::ShaderDataType::Float3, "a_Position" }
			});
		m_SquareVa->AddVertexBuffer(squareVb);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		std::shared_ptr<Dolan::IndexBuffer> squareIb;
		squareIb.reset(Dolan::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		m_SquareVa->SetIndexBuffer(squareIb);

		std::string vertexSrc = R"(
			#version 330 core
				
			layout(location = 0) in vec3 a_Position;		
			layout(location = 1) in vec4 a_Color;		

			uniform mat4 u_ViewProjection;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
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

		m_Shader.reset(new Dolan::Shader(vertexSrc, fragmentSrc));

		std::string blueShaderVertSrc = R"(
			#version 330 core
				
			layout(location = 0) in vec3 a_Position;		

			uniform mat4 u_ViewProjection;

			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
			}
		)";

		std::string blueShaderFragSrc = R"(
			#version 330 core
				
			layout(location = 0) out vec4 color;

			in vec3 v_Position;

			void main()
			{
				color = vec4(0.2, 0.3, 0.8, 1.0);
			}
		)";
		m_BlueShader.reset(new Dolan::Shader(blueShaderVertSrc, blueShaderFragSrc));
	}

	void OnUpdate() override
	{
		if (Dolan::Input::IsKeyPressed(DN_KEY_LEFT))
			m_CameraPos.x -= m_CameraMoveSpeed;
		else if (Dolan::Input::IsKeyPressed(DN_KEY_RIGHT))
			m_CameraPos.x += m_CameraMoveSpeed;
		
		if (Dolan::Input::IsKeyPressed(DN_KEY_UP))
			m_CameraPos.y += m_CameraMoveSpeed;
		else if (Dolan::Input::IsKeyPressed(DN_KEY_DOWN))
			m_CameraPos.y -= m_CameraMoveSpeed;

		if (Dolan::Input::IsKeyPressed(DN_KEY_A))
			m_CameraRot += m_CameraRotSpeed;
		if (Dolan::Input::IsKeyPressed(DN_KEY_D))
			m_CameraRot -= m_CameraRotSpeed;

		Dolan::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Dolan::RenderCommand::Clear();

		m_Camera.SetPosition(m_CameraPos);
		m_Camera.SetRotation(m_CameraRot);

		Dolan::Renderer::BeginScene(m_Camera);
		Dolan::Renderer::Submit(m_BlueShader, m_SquareVa);

		Dolan::Renderer::Submit(m_Shader, m_VertexArray);
		
		Dolan::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override
	{

	}

	void OnEvent(Dolan::Event& e) override
	{

	}

private:
	std::shared_ptr<Dolan::Shader> m_Shader;
	std::shared_ptr<Dolan::VertexArray> m_VertexArray;

	std::shared_ptr<Dolan::Shader> m_BlueShader;
	std::shared_ptr<Dolan::VertexArray> m_SquareVa;

	Dolan::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPos;
	float m_CameraRot = 0.0f;
	float m_CameraRotSpeed = 2.0f;
	float m_CameraMoveSpeed = 0.1f;
};

class Sandbox : public Dolan::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}

	~Sandbox()
	{

	}
};

Dolan::Application* Dolan::CreateApplication()
{
	return new Sandbox();
}