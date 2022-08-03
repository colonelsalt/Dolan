#include "dnpch.h"
#include "OpenGlShader.h"

#include <fstream>
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

namespace Dolan {
	
	static GLenum ShaderTypeFromString(const std::string& type)
	{
		if (type == "vertex")
			return GL_VERTEX_SHADER;
		else if (type == "fragment" || type == "pixel")
			return GL_FRAGMENT_SHADER;

		DN_CORE_ASSERT(false, "Unknown shader type.");
		return 0;
	}

	OpenGlShader::OpenGlShader(const std::string& filepath)
	{
		DN_PROFILE_FUNCTION();

		std::string rawSource = ReadFile(filepath);
		auto shaderSources = PreProcess(rawSource);

		Compile(shaderSources);

		// Extract name from file path
		size_t lastSlash = filepath.find_last_of("/\\");
		if (lastSlash == std::string::npos)
			lastSlash = 0;
		else
			lastSlash += 1;
		size_t lastDot = filepath.rfind('.');

		size_t nameLength = (lastDot == std::string::npos) ? filepath.size() - lastSlash : lastDot - lastSlash;
		m_Name = filepath.substr(lastSlash, nameLength);
	}

	OpenGlShader::OpenGlShader(const std::string& name, const std::string& vertSrc, const std::string& fragSrc)
		: m_Name(name)
	{
		DN_PROFILE_FUNCTION();

		std::unordered_map<GLenum, std::string> sources;
		sources[GL_VERTEX_SHADER] = vertSrc;
		sources[GL_FRAGMENT_SHADER] = fragSrc;

		Compile(sources);
	}

	std::string OpenGlShader::ReadFile(const std::string& filepath)
	{
		DN_PROFILE_FUNCTION();

		std::string result;
		std::ifstream in(filepath, std::ios::in | std::ios::binary);
		if (in)
		{
			in.seekg(0, std::ios::end);
			result.resize(in.tellg());
			in.seekg(0, std::ios::beg);
			in.read(&result[0], result.size());
			in.close();
		}
		else
		{
			DN_CORE_ERROR("Could not open file '{0}'", filepath);
		}

		return result;
	}

	std::unordered_map<GLenum, std::string> OpenGlShader::PreProcess(const std::string& source)
	{
		DN_PROFILE_FUNCTION();

		std::unordered_map<GLenum, std::string> shaderSources;

		const char* typeToken = "#type";
		size_t typeTokenLength = strlen(typeToken);
		size_t pos = source.find(typeToken, 0);
		while (pos != std::string::npos)
		{
			size_t eol = source.find_first_of("\r\n", pos);
			DN_CORE_ASSERT(eol != std::string::npos, "Syntax error.");

			size_t typeStart = pos + typeTokenLength + 1;
			std::string type = source.substr(typeStart, eol - typeStart);

			size_t nextLinePos = source.find_first_not_of("\r\n", eol);
			pos = source.find(typeToken, nextLinePos);
			shaderSources[ShaderTypeFromString(type)] =
				source.substr(nextLinePos, pos - nextLinePos);
		}

		return shaderSources;
	}

	void OpenGlShader::Compile(const std::unordered_map<GLenum, std::string>& shaderSources)
	{
		DN_PROFILE_FUNCTION();

		GLuint program = glCreateProgram();
		DN_CORE_ASSERT(shaderSources.size() <= 2, "Only 2 shaders supported for now.");
		std::array<GLenum, 2> glShaderIds;
		int i = 0;
		for (auto& [type, source] : shaderSources)
		{
			GLuint shader = glCreateShader(type);
			const char* src = source.c_str();
			glShaderSource(shader, 1, &src, nullptr);

			glCompileShader(shader);

			GLint didCompile = 0;
			glGetShaderiv(shader, GL_COMPILE_STATUS, &didCompile);
			if (didCompile == GL_FALSE)
			{
				GLint maxLength = 0;
				glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

				std::vector<GLchar> infoLog(maxLength);
				glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

				glDeleteShader(shader);

				DN_CORE_ERROR("{0}", infoLog.data());
				DN_CORE_ASSERT(false, "Failed to compile shader.");
				break;
			}

			glAttachShader(program, shader);
			glShaderIds[i++] = shader;
		}

		glLinkProgram(program);

		GLint didLink = 0;
		glGetProgramiv(program, GL_LINK_STATUS, (int*)&didLink);
		if (didLink == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

			glDeleteProgram(program);

			for (GLenum id : glShaderIds)
				glDeleteShader(id);

			DN_CORE_ERROR("{0}", infoLog.data());
			DN_CORE_ASSERT(false, "Error linking shaders.");
			return;
		}

		for (GLenum id : glShaderIds)
		{
			glDetachShader(program, id);
			glDeleteShader(id);
		}

		m_RendererId = program;
	}

	OpenGlShader::~OpenGlShader()
	{
		DN_PROFILE_FUNCTION();

		glDeleteProgram(m_RendererId);
	}

	void OpenGlShader::Bind() const
	{
		DN_PROFILE_FUNCTION();

		glUseProgram(m_RendererId);
	}

	void OpenGlShader::UnBind() const
	{
		DN_PROFILE_FUNCTION();

		glUseProgram(0);
	}

	void OpenGlShader::SetInt(const std::string& name, int value)
	{
		DN_PROFILE_FUNCTION();

		UploadUniformInt(name, value);
	}

	void OpenGlShader::SetFloat(const std::string& name, float value)
	{
		DN_PROFILE_FUNCTION();

		UploadUniformFloat(name, value);
	}

	void OpenGlShader::SetFloat3(const std::string& name, const glm::vec3& value)
	{
		UploadUniformFloat3(name, value);
	}

	void OpenGlShader::SetFloat4(const std::string& name, const glm::vec4& value)
	{
		UploadUniformFloat4(name, value);
	}

	void OpenGlShader::SetMat4(const std::string& name, const glm::mat4& value)
	{
		UploadUniformMat4(name, value);
	}

	void OpenGlShader::UploadUniformInt(const std::string& name, int value)
	{
		GLint location = glGetUniformLocation(m_RendererId, name.c_str());
		glUniform1i(location, value);
	}

	void OpenGlShader::UploadUniformFloat(const std::string& name, float value)
	{
		GLint location = glGetUniformLocation(m_RendererId, name.c_str());
		glUniform1f(location, value);
	}

	void OpenGlShader::UploadUniformFloat2(const std::string& name, const glm::vec2& values)
	{
		GLint location = glGetUniformLocation(m_RendererId, name.c_str());
		glUniform2f(location, values.x, values.y);
	}

	void OpenGlShader::UploadUniformFloat3(const std::string& name, const glm::vec3& values)
	{
		GLint location = glGetUniformLocation(m_RendererId, name.c_str());
		glUniform3f(location, values.x, values.y, values.z);
	}

	void OpenGlShader::UploadUniformFloat4(const std::string& name, const glm::vec4& values)
	{
		GLint location = glGetUniformLocation(m_RendererId, name.c_str());
		glUniform4f(location, values.x, values.y, values.z, values.w);
	}

	void OpenGlShader::UploadUniformMat3(const std::string& name, const glm::mat3& matrix)
	{
		GLint location = glGetUniformLocation(m_RendererId, name.c_str());
		glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}

	void OpenGlShader::UploadUniformMat4(const std::string& name, const glm::mat4& matrix)
	{
		GLint location = glGetUniformLocation(m_RendererId, name.c_str());
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}
}