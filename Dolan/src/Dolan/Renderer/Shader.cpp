#include "dnpch.h"
#include "Shader.h"

#include <glad/glad.h>

namespace Dolan {

	Shader::Shader(std::string vertSrc, std::string fragSrc)
	{
		// Create empty handle/ID for vertex shader
		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

		// Send source code for vertex shader to OpenGL
		const char* src = vertSrc.c_str();
		glShaderSource(vertexShader, 1, &src, nullptr);

		// Compile vertex shader
		glCompileShader(vertexShader);

		GLint didCompile = 0;
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &didCompile);
		if (didCompile == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);


			glDeleteShader(vertexShader);

			DN_CORE_ERROR("{0}", infoLog.data());
			DN_CORE_ASSERT(false, "Failed to compile vertex shader.");
			return;
		}

		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

		src = fragSrc.c_str();
		glShaderSource(fragmentShader, 1, &src, nullptr);

		glCompileShader(fragmentShader);

		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &didCompile);
		if (didCompile == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);

			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);

			DN_CORE_ERROR("{0}", infoLog.data());
			DN_CORE_ASSERT(false, "Failed to compile fragment shader.");
			return;
		}

		m_RendererId = glCreateProgram();

		glAttachShader(m_RendererId, vertexShader);
		glAttachShader(m_RendererId, fragmentShader);

		glLinkProgram(m_RendererId);

		GLint didLink = 0;
		glGetProgramiv(m_RendererId, GL_LINK_STATUS, (int*)&didLink);
		if (didLink == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(m_RendererId, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(m_RendererId, maxLength, &maxLength, &infoLog[0]);


			glDeleteProgram(m_RendererId);
			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);

			DN_CORE_ERROR("{0}", infoLog.data());
			DN_CORE_ASSERT(false, "Error linking shaders.");
			return;
		}

		glDetachShader(m_RendererId, vertexShader);
		glDetachShader(m_RendererId, fragmentShader);
	}

	Shader::~Shader()
	{
		glDeleteProgram(m_RendererId);
	}

	void Shader::Bind() const
	{
		glUseProgram(m_RendererId);
	}

	void Shader::UnBind() const
	{
		glUseProgram(0);
	}
}