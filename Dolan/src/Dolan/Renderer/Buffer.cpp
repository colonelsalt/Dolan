#include "dnpch.h"
#include "Buffer.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGlBuffer.h"

namespace Dolan {
	
	VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::GetApi())
		{
		case RendererApi::None:
			DN_CORE_ASSERT(false, "Renderer API 'NONE' is not supported");
			return nullptr;
		case RendererApi::OpenGL:
			return new OpenGlVertexBuffer(vertices, size);
		}

		DN_CORE_ASSERT(false, "Unknown Renderer API!");
		return nullptr;
	}

	IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t count)
	{
		switch (Renderer::GetApi())
		{
		case RendererApi::None:
			DN_CORE_ASSERT(false, "Renderer API 'NONE' is not supported");
			return nullptr;
		case RendererApi::OpenGL:
			return new OpenGlIndexBuffer(indices, count);
		}

		DN_CORE_ASSERT(false, "Unknown Renderer API!");
		return nullptr;
	}
}