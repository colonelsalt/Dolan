#include <Dolan.h>
#include <Dolan/Core/EntryPoint.h>

#include "EditorLayer.h"

namespace Dolan {
	class DolanEditor : public Application
	{
	public:
		DolanEditor()
			: Application("Dolan Editor")
		{
			//PushLayer(new ExampleLayer());
			PushLayer(new EditorLayer());
		}

		~DolanEditor()
		{

		}
	};

	Application* CreateApplication()
	{
		return new DolanEditor();
	}
}

