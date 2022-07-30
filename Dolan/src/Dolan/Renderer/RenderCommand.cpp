#include "dnpch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGlRendererApi.h"

namespace Dolan {

	Scope<RendererApi> RenderCommand::s_RendererApi = RendererApi::Create();

}