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
		virtual void Init() = 0;
		virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) = 0;
		virtual void SetClearColor(const glm::vec4& color) = 0;
		virtual void Clear() = 0;

		virtual void DrawIndexed(const Ref<VertexArray>& vertexArray) = 0;

		inline static Api GetApi() { return s_Api; }
		static Scope<RendererApi> Create();
	private:
		static Api s_Api;
	};

}