#include "Sandbox2d.h"

#include <imgui/imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Platform/OpenGL/OpenGlShader.h"

#include <chrono>

template <typename Fn>
class Timer
{
public:
	Timer(const char* name, Fn&& func)
		: m_Name(name), m_Func(func), m_Stopped(false)
	{
		m_StartTimePoint = std::chrono::high_resolution_clock::now();
	}

	~Timer()
	{
		if (!m_Stopped)
			Stop();
	}

	void Stop()
	{
		auto endTime = std::chrono::high_resolution_clock::now();
		
		long long start = std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimePoint).time_since_epoch().count();
		long long end = std::chrono::time_point_cast<std::chrono::microseconds>(endTime).time_since_epoch().count();

		m_Stopped = true;
		float duration = (end - start) * 0.001f;

		m_Func({ m_Name, duration });
	}

private:
	const char* m_Name;
	Fn m_Func;
	bool m_Stopped;
	std::chrono::time_point<std::chrono::steady_clock> m_StartTimePoint;
};

#define PROFILE_SCOPE(name) Timer timer##__LINE__(name, [&](ProfileResult profileResult) { m_ProfileResults.push_back(profileResult); })

Sandbox2d::Sandbox2d()
	: Layer("Sandbox2d"), m_CameraController(1280.0f / 720.0f)
{
}

void Sandbox2d::OnAttach()
{
	m_CheckerboardTexture = Dolan::Texture2d::Create("assets/textures/Checkerboard.png");
}

void Sandbox2d::OnDetach()
{

}

void Sandbox2d::OnUpdate(Dolan::Timestep ts)
{
	PROFILE_SCOPE("Sandbox2d::OnUpdate");

	{
		PROFILE_SCOPE("CameraController::OnUpdate");
		m_CameraController.OnUpdate(ts);
	}

	{
		PROFILE_SCOPE("Renderer prep");
		Dolan::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Dolan::RenderCommand::Clear();
	}

	{
		PROFILE_SCOPE("Renderer draw");
		Dolan::Renderer2d::BeginScene(m_CameraController.GetCamera());

		Dolan::Renderer2d::DrawQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, { 0.8f, 0.2f, 0.3f, 1.0f });
		Dolan::Renderer2d::DrawQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, { 0.2f, 0.3f, 0.8f, 1.0f });
		Dolan::Renderer2d::DrawQuad({ 0.2f, 0.5f, -0.1f }, { 10.0f, 10.0f }, m_CheckerboardTexture);

		Dolan::Renderer2d::EndScene();
	}
}

void Sandbox2d::OnImGuiRender()
{
	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Square colour", glm::value_ptr(m_SquareColor));

	for (ProfileResult& result : m_ProfileResults)
	{
		char label[50];
		strcpy(label, "%3fms ");
		strcat(label, result.Name);

		ImGui::Text(label, result.Time);
	}
	m_ProfileResults.clear();
	
	ImGui::End();
}

void Sandbox2d::OnEvent(Dolan::Event& e)
{
	m_CameraController.OnEvent(e);
}
