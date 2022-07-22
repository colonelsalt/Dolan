#pragma once

namespace Dolan {

	enum class RendererApi
	{
		None = 0, OpenGL = 1
	};
	class Renderer
	{
	public:
		inline static RendererApi GetApi() { return s_RendererApi; }
	private:
		static RendererApi s_RendererApi;
	};


}