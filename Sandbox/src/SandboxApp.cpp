#include <Dolan.h>

class ExampleLayer : public Dolan::Layer
{
public:
	ExampleLayer()
		: Dolan::Layer("ExampleLayer") {}

	void OnUpdate() override
	{
		// DN_TRACE("Sandbox updating...");
		if (Dolan::Input::IsKeyPressed(DN_KEY_TAB))
			DN_TRACE("Tab key pressed!");
	}

	void OnEvent(Dolan::Event& e) override
	{
		if (e.GetEventType() == Dolan::EventType::KeyPressed)
		{
			Dolan::KeyPressedEvent& keyPressedEvent = (Dolan::KeyPressedEvent&)e;
			DN_TRACE("{0}", (char)keyPressedEvent.GetKeyCode());
		}
	}
};

class Sandbox : public Dolan::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
		PushOverlay(new Dolan::ImGuiLayer());
	}

	~Sandbox()
	{

	}
};

Dolan::Application* Dolan::CreateApplication()
{
	return new Sandbox();
}