#include "dnpch.h"
#include "Texture.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGlTexture.h"

namespace Dolan {

	Ref<Texture2d> Texture2d::Create(uint32_t width, uint32_t height)
	{
		switch (Renderer::GetApi())
		{
			case RendererApi::Api::None:
				DN_CORE_ASSERT(false, "Unknown renderer API.");
				return nullptr;
			case RendererApi::Api::OpenGL:
				return CreateRef<OpenGlTexture2d>(width, height);
		}

		DN_CORE_ASSERT(false, "Unknown renderer API.");
		return nullptr;
	}

	Ref<Texture2d> Texture2d::Create(const std::string& path)
	{
		switch (Renderer::GetApi())
		{
			case RendererApi::Api::None:
				DN_CORE_ASSERT(false, "Unknown renderer API.");
				return nullptr;
			case RendererApi::Api::OpenGL:
				return CreateRef<OpenGlTexture2d>(path);
		}

		DN_CORE_ASSERT(false, "Unknown renderer API.");
		return nullptr;
	}

}