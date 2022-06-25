#include <Dolan.h>

class Sandbox : public Dolan::Application
{
public:
	Sandbox()
	{

	}

	~Sandbox()
	{

	}
};

Dolan::Application* Dolan::CreateApplication()
{
	return new Sandbox();
}