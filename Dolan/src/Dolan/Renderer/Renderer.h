#pragma once

#include "RenderCommand.h"
#include "OrthographicCamera.h"
#include "Shader.h"

namespace Dolan {

	class Renderer
	{
	public:
		static void BeginScene(OrthographicCamera& camera);
		static void EndScene();

		static void Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray);

		inline static RendererApi::Api GetApi() { return RendererApi::GetApi(); }
	private:
		struct SceneData
		{
			glm::mat4 ViewProjectionMatrix;
		};
		static SceneData* s_SceneData;
	};


}