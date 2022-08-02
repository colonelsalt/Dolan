#include <Dolan.h>
#include <Dolan/Core/EntryPoint.h>

#include "Sandbox2d.h"
#include "ExampleLayer.h"

class Sandbox : public Dolan::Application
{
public:
	Sandbox()
	{
		//PushLayer(new ExampleLayer());
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