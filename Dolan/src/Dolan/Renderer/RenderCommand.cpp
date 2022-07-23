#include "dnpch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGlRendererApi.h"

namespace Dolan {

	RendererApi* RenderCommand::s_RendererApi = new OpenGlRendererApi();

}