#pragma once

#include <glm/glm.hpp>
#include "VertexArray.h"

namespace Dolan {

	class RendererApi
	{
	public:
		enum class Api
		{
			None = 0, OpenGL = 1
		};
	public:
		virtual void SetClearColor(const glm::vec4& color) = 0;
		virtual void Clear() = 0;

		virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) = 0;

		inline static Api GetApi() { return s_Api; }
	private:
		static Api s_Api;
	};

}