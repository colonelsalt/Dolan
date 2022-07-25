#include "dnpch.h"
#include "Texture.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGlTexture.h"

namespace Dolan {

	Ref<Texture2d> Texture2d::Create(const std::string& path)
	{
		switch (Renderer::GetApi())
		{
			case RendererApi::Api::None:
				DN_CORE_ASSERT(false, "Unknown renderer API.");
				return nullptr;
			case RendererApi::Api::OpenGL:
				return std::make_shared<OpenGlTexture2d>(path);
		}

		DN_CORE_ASSERT(false, "Unknown renderer API.");
		return nullptr;
	}

}