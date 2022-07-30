#include "dnpch.h"
#include "Shader.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGlShader.h"

namespace Dolan {

	Ref<Shader> Shader::Create(const std::string& filepath)
	{
		switch (Renderer::GetApi())
		{
		case RendererApi::Api::None:
			DN_CORE_ASSERT(false, "Unknown renderer API.");
			return nullptr;
		case RendererApi::Api::OpenGL:
			return CreateRef<OpenGlShader>(filepath);
		}

		DN_CORE_ASSERT(false, "Unknown renderer API.");
		return nullptr;
	}

	Ref<Shader> Shader::Create(const std::string& name, const std::string& vertSrc, const std::string& fragSrc)
	{
		switch (Renderer::GetApi())
		{
			case RendererApi::Api::None:
				DN_CORE_ASSERT(false, "Unknown renderer API.");
				return nullptr;
			case RendererApi::Api::OpenGL:
				return CreateRef<OpenGlShader>(name, vertSrc, fragSrc);
		}

		DN_CORE_ASSERT(false, "Unknown renderer API.");
		return nullptr;
	}

	void ShaderLibrary::Add(const std::string& name, const Ref<Shader>& shader)
	{
		DN_CORE_ASSERT(!Exists(name), "Shader already exists.");
		m_Shaders[name] = shader;
	}

	void ShaderLibrary::Add(const Ref<Shader>& shader)
	{
		const std::string& name = shader->GetName();
		Add(name, shader);
	}

	Ref<Shader> ShaderLibrary::Load(const std::string& filepath)
	{
		Ref<Shader> shader = Shader::Create(filepath);
		Add(shader);
		return shader;
	}

	Ref<Shader> ShaderLibrary::Load(const std::string& name, const std::string& filepath)
	{
		Ref<Shader> shader = Shader::Create(filepath);
		Add(name, shader);
		return shader;
	}

	Ref<Shader> ShaderLibrary::Get(const std::string& name)
	{
		DN_CORE_ASSERT(Exists(name), "Shader does not exist.");
		return m_Shaders[name];
	}

	bool ShaderLibrary::Exists(const std::string& shaderName) const
	{
		return m_Shaders.find(shaderName) != m_Shaders.end();
	}

}