#pragma once

#include <string>

namespace Dolan {

	class Shader
	{
	public:
		virtual ~Shader() = default;

		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;

		static Shader* Create(std::string& vertSrc, std::string& fragSrc);
	};

}