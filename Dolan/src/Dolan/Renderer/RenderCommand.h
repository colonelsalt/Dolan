#pragma once

#include "RendererApi.h"

namespace Dolan {

	class RenderCommand
	{
	public:
		inline static void Init()
		{
			s_RendererApi->Init();
		}

		inline static void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
		{
			s_RendererApi->SetViewport(x, y, width, height);
		}

		inline static void SetClearColor(const glm::vec4& color)
		{
			s_RendererApi->SetClearColor(color);
		}

		inline static void Clear()
		{
			s_RendererApi->Clear();
		}

		inline static void DrawIndexed(const Ref<VertexArray>& vertexArray)
		{
			s_RendererApi->DrawIndexed(vertexArray);
		}
	private:
		static RendererApi* s_RendererApi;
	};

}