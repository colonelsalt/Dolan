#pragma once

#include "Dolan/Renderer/RendererApi.h"

namespace Dolan {

	class OpenGlRendererApi : public RendererApi
	{
	public:
		virtual void Init() override;
		virtual void SetClearColor(const glm::vec4& color) override;
		virtual void Clear() override;

		virtual void DrawIndexed(const Ref<VertexArray>& vertexArray) override;
	};

}