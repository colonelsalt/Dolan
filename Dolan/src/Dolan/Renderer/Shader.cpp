#include "dnpch.h"
#include "Shader.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGlShader.h"

namespace Dolan {

	Shader* Shader::Create(const std::string& filepath)
	{
		switch (Renderer::GetApi())
		{
		case RendererApi::Api::None:
			DN_CORE_ASSERT(false, "Unknown renderer API.");
			return nullptr;
		case RendererApi::Api::OpenGL:
			return new OpenGlShader(filepath);
		}

		DN_CORE_ASSERT(false, "Unknown renderer API.");
		return nullptr;
	}

	Shader* Shader::Create(const std::string& vertSrc, const std::string& fragSrc)
	{
		switch (Renderer::GetApi())
		{
			case RendererApi::Api::None:
				DN_CORE_ASSERT(false, "Unknown renderer API.");
				return nullptr;
			case RendererApi::Api::OpenGL:
				return new OpenGlShader(vertSrc, fragSrc);
		}

		DN_CORE_ASSERT(false, "Unknown renderer API.");
		return nullptr;
	}

}