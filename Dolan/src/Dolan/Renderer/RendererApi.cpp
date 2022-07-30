#include "dnpch.h"
#include "RendererApi.h"

#include "Platform/OpenGL/OpenGlRendererApi.h"

namespace Dolan {

	RendererApi::Api RendererApi::s_Api = RendererApi::Api::OpenGL;

	Scope<RendererApi> RendererApi::Create()
	{
		switch (s_Api)
		{
			case RendererApi::Api::None:    DN_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererApi::Api::OpenGL:  return CreateScope<OpenGlRendererApi>();
		}

		DN_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}