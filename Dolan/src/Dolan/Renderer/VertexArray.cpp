#include "dnpch.h"
#include "VertexArray.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGlVertexArray.h"

namespace Dolan {

	VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetApi())
		{
		case RendererApi::None:
			DN_CORE_ASSERT(false, "Unknown renderer API.");
			return nullptr;
		case RendererApi::OpenGL:
			return new OpenGlVertexArray();
		}

		DN_CORE_ASSERT(false, "Unknown renderer API.");
		return nullptr;
	}

}