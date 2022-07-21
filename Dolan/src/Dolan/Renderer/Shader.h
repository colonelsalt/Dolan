#pragma once

#include <string>

namespace Dolan {

	class Shader
	{
	public:
		Shader(std::string vertSrc, std::string fragSrc);
		~Shader();

		void Bind() const;
		void UnBind() const;
	private:
		uint32_t m_RendererId;
	};

}