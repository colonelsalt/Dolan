#include "dnpch.h"
#include "FrameBuffer.h"

#include "Dolan/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGlFrameBuffer.h"

namespace Dolan {

	Ref<FrameBuffer> FrameBuffer::Create(const FrameBufferSpec& spec)
	{
		switch (Renderer::GetApi())
		{
			case RendererApi::Api::None:
				DN_CORE_ASSERT(false, "Renderer API 'NONE' is not supported");
				return nullptr;
			case RendererApi::Api::OpenGL:
				return CreateRef<OpenGlFrameBuffer>(spec);
		}

		DN_CORE_ASSERT(false, "Unknown Renderer API!");
		return nullptr;
	}

}