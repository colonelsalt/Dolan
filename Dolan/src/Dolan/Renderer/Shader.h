#pragma once

#include <string>
#include <glm/glm.hpp>

namespace Dolan {

	class Shader
	{
	public:
		Shader(std::string vertSrc, std::string fragSrc);
		~Shader();

		void Bind() const;
		void UnBind() const;

		void UploadUniformMat4(const std::string& name, const glm::mat4& uniform);
	private:
		uint32_t m_RendererId;
	};

}