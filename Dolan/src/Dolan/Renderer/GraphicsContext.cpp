#include "dnpch.h"
#include "GraphicsContext.h"

#include "Dolan/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGlContext.h"

namespace Dolan {

	Scope<GraphicsContext> GraphicsContext::Create(void* window)
	{
		switch (Renderer::GetApi())
		{
		case RendererApi::Api::None:
			DN_CORE_ASSERT(false, "Rendererer API is set to NONE.");
			return nullptr;
		case RendererApi::Api::OpenGL:
			return CreateScope<OpenGlContext>(static_cast<GLFWwindow*>(window));
		}
		DN_CORE_ASSERT(false, "Unknown renderer API.");
		return nullptr;
	}

}