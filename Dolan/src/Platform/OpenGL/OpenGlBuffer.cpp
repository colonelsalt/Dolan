#include "dnpch.h"
#include "OpenGlBuffer.h"

#include <glad/glad.h>

namespace Dolan {
	
	// ------------------------------------------------------------------------------------------------
	// VertexBuffer ------------------------------------------------------------------------------------
	// ------------------------------------------------------------------------------------------------

	OpenGlVertexBuffer::OpenGlVertexBuffer(uint32_t size)
	{
		DN_PROFILE_FUNCTION();

		glCreateBuffers(1, &m_RendererId);
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererId);
		glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
	}

	OpenGlVertexBuffer::OpenGlVertexBuffer(float* vertices, uint32_t size)
	{
		DN_PROFILE_FUNCTION();

		glCreateBuffers(1, &m_RendererId);
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererId);
		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
	}

	OpenGlVertexBuffer::~OpenGlVertexBuffer()
	{
		DN_PROFILE_FUNCTION();

		glDeleteBuffers(1, &m_RendererId);
	}

	void OpenGlVertexBuffer::Bind() const
	{
		DN_PROFILE_FUNCTION();

		glBindBuffer(GL_ARRAY_BUFFER, m_RendererId);
	}

	void OpenGlVertexBuffer::Unbind() const
	{
		DN_PROFILE_FUNCTION();

		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void OpenGlVertexBuffer::SetData(const void* data, uint32_t size)
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererId);
		// Send data from `data` into vertex buffer on GPU
		glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
	}

	// ------------------------------------------------------------------------------------------------
	// IndexBuffer ------------------------------------------------------------------------------------
	// ------------------------------------------------------------------------------------------------

	OpenGlIndexBuffer::OpenGlIndexBuffer(uint32_t* indices, uint32_t count)
		: m_Count(count)
	{
		DN_PROFILE_FUNCTION();

		glCreateBuffers(1, &m_RendererId);
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererId);
		glBufferData(GL_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
	}

	OpenGlIndexBuffer::~OpenGlIndexBuffer()
	{
		DN_PROFILE_FUNCTION();

		glDeleteBuffers(1, &m_RendererId);
	}

	void OpenGlIndexBuffer::Bind() const
	{
		DN_PROFILE_FUNCTION();

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererId);
	}

	void OpenGlIndexBuffer::Unbind() const
	{
		DN_PROFILE_FUNCTION();

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
}