#include "dnpch.h"
#include "Buffer.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGlBuffer.h"

namespace Dolan {
	
	Ref<VertexBuffer> VertexBuffer::Create(uint32_t size)
	{
		switch (Renderer::GetApi())
		{
		case RendererApi::Api::None:
			DN_CORE_ASSERT(false, "Renderer API 'NONE' is not supported");
			return nullptr;
		case RendererApi::Api::OpenGL:
			return CreateRef<OpenGlVertexBuffer>(size);
		}

		DN_CORE_ASSERT(false, "Unknown Renderer API!");
		return nullptr;
	}

	Ref<VertexBuffer> VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::GetApi())
		{
		case RendererApi::Api::None:
			DN_CORE_ASSERT(false, "Renderer API 'NONE' is not supported");
			return nullptr;
		case RendererApi::Api::OpenGL:
			return CreateRef<OpenGlVertexBuffer>(vertices, size);
		}

		DN_CORE_ASSERT(false, "Unknown Renderer API!");
		return nullptr;
	}

	Ref<IndexBuffer> IndexBuffer::Create(uint32_t* indices, uint32_t count)
	{
		switch (Renderer::GetApi())
		{
		case RendererApi::Api::None:
			DN_CORE_ASSERT(false, "Renderer API 'NONE' is not supported");
			return nullptr;
		case RendererApi::Api::OpenGL:
			return CreateRef<OpenGlIndexBuffer>(indices, count);
		}

		DN_CORE_ASSERT(false, "Unknown Renderer API!");
		return nullptr;
	}
}