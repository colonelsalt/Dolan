#include <Dolan.h>

class ExampleLayer : public Dolan::Layer
{
public:
	ExampleLayer()
		: Dolan::Layer("ExampleLayer") {}

	void OnUpdate() override
	{
		DN_TRACE("Sandbox updating...");
	}

	void OnEvent(Dolan::Event& e) override
	{
		DN_TRACE("{0}", e);
	}
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